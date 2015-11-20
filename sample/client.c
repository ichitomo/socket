#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main()
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    // if (argc < 3) {//引数の総数が3つ以下の時
    //    fprintf(stderr,"usage %s hostname port\n", argv[0]);//0番目の引数
    //    exit(0);
    // }
    portno = atoi("9999");//2番目の引数＝ポート番号
    while(1){
 
        sockfd = socket(AF_INET, SOCK_STREAM, 0);//ソケットの生成
        if (sockfd < 0) 
            error("ERROR opening socket");
        server = gethostbyname("localhost");//1番目の引数＝ホスト名
        if (server == NULL) {
            fprintf(stderr,"ERROR, no such host\n");
            exit(0);
        }

        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *)server->h_addr, 
             (char *)&serv_addr.sin_addr.s_addr,
             server->h_length);
        serv_addr.sin_port = htons(portno);
        if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
            error("ERROR connecting");
            printf("Please enter the message: ");
            bzero(buffer,256);
            fgets(buffer,255,stdin);
            n = write(sockfd,buffer,strlen(buffer));//データの発信
            if (n < 0) 
                 error("ERROR writing to socket");
            bzero(buffer,256);
            n = read(sockfd,buffer,255);//データの受信
            if (n < 0) 
                 error("ERROR reading from socket");
            printf("%s\n",buffer);
        
        close(sockfd);
    }
    return 0;
}
// int i;
    
//     printf("引数の総個数 = %d\n", argc);
//     for (i = 0; i < argc; i++) {
//         printf("%d番目の引数 = %s\n", i, argv[i]);
//     }
//     return 0;
