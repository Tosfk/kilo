#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

void enableRawMode() {
    struct termios raw;

    tcgetattr(STDIN_FILENO, &raw);

    raw.c_lflag &= ~(ECHO);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
// 终端的规范模式是它的默认模式。一般要在需要行编辑的交互式命令行场景里使用。
// 你的输入会先放到缓冲区中，按下回车键或者EOF后才能read()到数据。
// 支持退格键、CTRL+U（删除整行），字符会自动显示在屏幕上。
//
// 终端的原始模式是特殊的非规范模式，它是会及时响应每一个按键。
// 可以用在编辑器或者游戏中，它可以即时读取你敲下的字节，你每敲下一个，它都会传给程序，不用换行符。
//后终端的行编辑特殊字符，比如CTRL+C的处理会被关闭，数据原样传递。
//
// 两种模式通常通过修改 termios 结构体的标志位来切换。


int main() {
    enableRawMode();
    char c;
    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q');
    return 0;
}
