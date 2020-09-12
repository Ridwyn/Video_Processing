extern "C" {
#include <avcodec.h>
#include <avformat.h>
#include <swscale.h>
#include <error.h>

// #include <inttypes.h>
}

#include <iostream>

// #pragma comment(lib, "avcodec.lib")
// #pragma comment(lib, "avformat.lib")

bool load_frame(const char* filename, int* width_out, int* height_out, unsigned char** data_out){
 
    // Open file using libavformat
    AVFormatContext *av_format_ctx = avformat_alloc_context();
    if(!av_format_ctx){
        printf("couldnot create a avformat context");
        return false;
    }
    if(avformat_open_input(&av_format_ctx, filename, NULL, NULL) !=0){   
        printf("couldnt open video file\n");
        return false;
    }

    int video_stream_index = -1;
    AVCodecParameters* av_codec_params ;
    AVCodec* av_codec;

    // Find first valid video stream inside file
    for(unsigned int i = 0; i < av_format_ctx->nb_streams; i++){
        auto stream = av_format_ctx->streams[i];
        av_codec_params = av_format_ctx->streams[i]->codecpar;
        av_codec = avcodec_find_decoder(av_codec_params->codec_id);

        if(!av_codec){
            continue;
        }
        if(av_codec_params->codec_type == AVMEDIA_TYPE_VIDEO){
            video_stream_index = i;
            break;
        }
    }
    if(video_stream_index == -1){
        printf("Couldn't find valide video stream insde file\n");
        return false;
    }

    // Set up codec context for decoder
    AVCodecContext* av_codec_ctx = avcodec_alloc_context3(av_codec);
    if(!av_codec_ctx){
        printf("Couldn't create AVCodecContext\n");
        return false;
    }
    // Pass avdecoder params
    if(avcodec_parameters_to_context(av_codec_ctx, av_codec_params) < 0){
        printf("Couldn't inititlaise AVCodecContext\n");
        return false;
    }
    // Open avdecoder
    if(avcodec_open2(av_codec_ctx, av_codec, NULL) < 0){
        printf("couldn't open codec\n");
        return false;
    }

    // Create AVPacket  and AVFrame;
    AVFrame* av_frame = av_frame_alloc();
    if(!av_frame){
        printf("Couldn't allocate AVFrame\n");
        return false;
    }

    AVPacket* av_packet = av_packet_alloc();
    if(!av_packet){
        printf("Couldn't allocate AVPacket\n");
        return false;
    }

    // Itrerate to find first video packet
    int response;
    while(av_read_frame(av_format_ctx, av_packet) >= 0){
        if(av_packet->stream_index != video_stream_index){
            continue;
        }
        // Send  first video packet to decoder
        response = avcodec_send_packet(av_codec_ctx, av_packet);
        if(response < 0){
            printf("Failed to decode packet %s\n",""+response);
            return false;
        }
        // Receve decoded packet as Frame;
        response = avcodec_receive_frame(av_codec_ctx, av_frame);
        if(response == AVERROR(EAGAIN || response == AVERROR_EOF)){
            continue;
        }else if(response < 0){
            printf("Failed o decde packet: %s\n", ""+response);
            return false;
        }

        av_packet_unref(av_packet);
        break;
    }
    
    // unsigned char* data = new unsigned char[av_frame->width * av_frame->height * 3];
    // for (int x = 0; x < av_frame->width ; x++)
    // {
    //     for (int y = 0; y < av_frame->height; y++)
    //     {
    //         data[y * av_frame->width * 3 + x * 3 ] = av_frame->data[0][y * av_frame->linesize[0] + x];
    //         data[y * av_frame->width * 3 + x * 3 + 1] =av_frame->data[0][y * av_frame->linesize[0] + x];
    //         data[y * av_frame->width * 3 + x * 3 + 2] =av_frame->data[0][y * av_frame->linesize[0] + x];

    //     }
    // }

    
    uint8_t* data = new uint8_t[av_frame->width * av_frame->height * 4];
    SwsContext* sws_scaler_ctx = sws_getContext(av_frame->width, av_frame->height, av_codec_ctx->pix_fmt,
                                                av_frame->width, av_frame->height, AV_PIX_FMT_RGB0,
                                                SWS_BILINEAR, NULL,NULL,NULL);
    
    if (!sws_scaler_ctx){
        printf("Couldn't inititalize sw scaler\n");
        return false;
    }

    uint8_t* dest[4] = {data,NULL, NULL, NULL};
    int dest_linesize[4] = {av_frame->width * 4, 0, 0, 0 };
    sws_scale(sws_scaler_ctx, av_frame->data, av_frame->linesize,0, av_frame->height,dest, dest_linesize);  
    sws_freeContext(sws_scaler_ctx);

    // Send back information to pointers
    *width_out = av_frame->width;
    *height_out = av_frame->height;
    *data_out = data;


    // Close format input to close file
    avformat_close_input(&av_format_ctx);
    // Free all Allocated memory
    avformat_free_context(av_format_ctx);
    avcodec_free_context(&av_codec_ctx);
    av_frame_free(&av_frame);
    av_packet_free(&av_packet);

    return true;
}