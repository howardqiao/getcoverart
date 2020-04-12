#ifdef __cplusplus
extern "C" {
#endif
#include <libavcodec/avcodec.h> 
#include <libavformat/avformat.h>
#ifdef __cplusplus 
}
#endif

void retrieve_album_art(const char *path, const char *album_art_file) {
    int i, ret = 0;

    if (!path) {
        printf("Path is NULL\n");
        return;
    }

    AVFormatContext *pFormatCtx = avformat_alloc_context();

    printf("Opening %s\n", path);

    // open the specified path
    if (avformat_open_input(&pFormatCtx, path, NULL, NULL) != 0) {
        printf("avformat_open_input() failed\n");
        goto fail;
    }

    // read the format headers
    if (pFormatCtx->iformat->read_header(pFormatCtx) < 0) {
        printf("could not read the format header\n");
        goto fail;
    }

    // find the first attached picture, if available
    for (i = 0; i < pFormatCtx->nb_streams; i++)
        if (pFormatCtx->streams[i]->disposition & AV_DISPOSITION_ATTACHED_PIC) {
            AVPacket pkt = pFormatCtx->streams[i]->attached_pic;
            FILE* album_art = fopen(album_art_file, "wb");
            ret = fwrite(pkt.data, pkt.size, 1, album_art);
            fclose(album_art);
            av_packet_unref(&pkt);
            break;
        }

    if (ret) {
        printf("Wrote album art to %s\n", album_art_file);
    }

    fail:
        ;//printf("failed\n");
}

int main(int argc,char **argv) {
    avformat_network_init();
//    av_register_all();

    if (argc != 3){
        printf("usage: getcover uri filename\n");
    } else {
        retrieve_album_art(argv[1], argv[2]);
    }

    return 0;
}
