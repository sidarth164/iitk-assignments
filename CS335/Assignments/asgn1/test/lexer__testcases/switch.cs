// int main(int na, char* argv[])
// {
//     int wflg = 0, tflg = 0;
//     int dflg = 0;
//     char c;
//     switch(c)
//     {
//         case 'w':
//         case 'W':
//             wflg = 1;
//             break;
//         case 't':
//         case 'T':
//             tflg = 1;
//             break;
//         case 'd':
//             dflg = 1;
//             break;
//     }
//     return 0;
// }

using System;

public class Test
{
    public int Main(string[] argv)
    {
        int wflg = 0, tflg = 0;
        int dflg = 0;
        char c;
        switch(c)
        {
            case 'w':
            case 'W':
                wflg = 1;
                break;
            case 't':
            case 'T':
                tflg = 1;
                break;
            case 'd':
                dflg = 1;
                break;
        }
        return 0;
    }

}