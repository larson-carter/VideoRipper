#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void downloadVideo(const char *url) {
    // Remove existing video file if it exists
    remove("video.mp4");

    // Use system call to download video using yt-dlp
    char command[1000];
    sprintf(command, "yt-dlp -o video.mp4 -f mp4 \"%s\"", url);
    system(command);
}

void createPlaylistFile() {
    // Remove existing playlist file if it exists
    remove("video_playlist.m3u");

    // Create M3U playlist file
    FILE *playlist = fopen("video_playlist.m3u", "w");
    if (playlist == NULL) {
        printf("Error creating playlist file\n");
        return;
    }

    // Write playlist entries
    fprintf(playlist, "#EXTM3U\n");
    fprintf(playlist, "#EXTINF:-1,YouTube Video\n");
    fprintf(playlist, "video.mp4\n"); // Use local file path instead of URL

    fclose(playlist);
}

void openVLC() {
    // Use system call to close any running instance of VLC
    system("pkill vlc");

    // Use system call to open VLC with the playlist
    system("vlc video_playlist.m3u &");
}

int main() {
    char url[1000];

    printf("Enter the YouTube video URL: ");
    scanf("%999[^\n]", url);
    getchar(); // Consume newline character

    // Start downloading the video
    downloadVideo(url);

    // Wait for the download process to finish
    printf("Downloading video...\n");
    wait(NULL);
    printf("Video downloaded successfully\n");

    // Create the playlist file
    createPlaylistFile();

    // Open VLC with the playlist
    openVLC();

    printf("Playlist created and VLC opened successfully\n");

    return 0;
}
