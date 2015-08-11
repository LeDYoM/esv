#include "mvcontroller.h"

int main(int argc, char *argv[])
{
    MVController app(argc, argv);
	
    int result=app.exec();
    return result;
}
