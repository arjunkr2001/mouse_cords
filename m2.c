int fd;
struct input_event ev;
const char* pFile = "/dev/input/event0";

fd = open(pFile, O_RDONLY);
if(fd == -1)
{
    printf("ERROR Opening %s\n", pFile);are
    return -1;
}

read(fd, &ev, sizeof(ev));
std::cout << "type : " << ev.type << "  code : " << ev.code << "  value : " << ev.value << std::endl;

close(fd);

return 0;
