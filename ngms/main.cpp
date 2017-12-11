#include <QCoreApplication>
#include "GreenAmpt.h"
/*
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    return a.exec();
}*/

int main()
{
   static int IROF=0;
    int IT=1;
    double RINT[NSTEP];
    double DF=0;
    double CUMF=0;
    double p;
    ifstream inf;
    ofstream outf;
    inf.open("../data/test.txt");
    outf.open("out.txt");
    while(inf>>p)
    {
           if(p>0)
        {
            RINT[IT-1]=p/DT;
             IT++;
        }
        else
        {
            RINT[IT-1]=0;
                    IT++;
        }

    }
    for(IT=1; IT<=NSTEP; IT++)
    {
        if(RINT[IT-1]!=0)
        {
            double temp=EXPINF(IROF,IT,RINT[IT-1],DF,CUMF);
            outf<<IT;
            outf<<" ";
            outf<<temp;
            outf<<endl;
        }

    }
    inf.close();
    outf.close();



    return 0;
}
