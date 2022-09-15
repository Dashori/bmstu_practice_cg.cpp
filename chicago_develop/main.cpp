#include "mainwindow.h"


int parseArguments(MainWindow &w, int argc, char *argv[]);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    if (parseArguments(w, argc, argv))
        return EXIT_SUCCESS;

    w.show();

    return a.exec();
}


int parseArguments(MainWindow &w, int argc, char *argv[])
{
    for (int i = 0; i < argc; i++)
    {
        if (!strcmp(argv[i], "-scene"))
        {
            w.setScene(argv[i + 1]);
        }

        if (!strcmp(argv[i], "-image"))
        {
            w.setImageFlag(argv[i + 1]);
            w.getImage();

            return EXIT_PROGRAM;
        }

        if (!strcmp(argv[i], "-film"))
        {
            int num = std::stoi(argv[i+1]);

            for (int i = 0; i < 10; i++)
            {
                w.on_rotateY_clicked();

                std::string filename = "./film/film" + std::to_string(num + i) + ".png";
                w.setImageFlag(filename);
                w.getImage();
            }

            return EXIT_PROGRAM;
       }

       if (!strcmp(argv[i], "-test"))
       {
           QTest::qExec(new TestTriangle);

           return EXIT_PROGRAM;
       }

       if (!strcmp(argv[i], "-research"))
       {

           using std::chrono::duration_cast;
           using std::chrono::microseconds;

           auto start = std::chrono::steady_clock::now();
           auto end = std::chrono::steady_clock::now();

           start = std::chrono::steady_clock::now();
           w.getImage();
           end = std::chrono::steady_clock::now();

           std::cout << w.getSceneCountFaces() << " ";
           std::cout << std::fixed << (int)duration_cast<microseconds>(end - start).count() << " \n";

           return EXIT_PROGRAM;
       }
   }

   return EXIT_SUCCESS;
}
