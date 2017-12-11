#include <iostream>
#include <math.h>
#include <fstream>
using namespace std;
const int NSTEP   =366;
const double DT   =24;
const double SZM  =0.000501;
const double HF   =0.1;
const double DTH  =0.36;
const double XK0  =3.0;
//double  EXPINF(int IROF,int IT,double RINT,double  DF,double CUMF);

double  EXPINF(int IROF,int IT,double RINT,double  DF,double CUMF)
{


    double CD   =HF*DTH;
    double XKF  =XK0;
    double SZF  =1.0/SZM;
    double CONST=0;
    double FC=0;
    double FUNC=0;
    double SUM=0;  //
    double E    =0.00001;
    double FAC;
    double F;
    double F1;
    double F2;
    double R2;
    double TP;
    double ADD;
    double DFUNC;
    if(IROF!=1)
    {
        if(CUMF==0)
        {
            F2=CUMF+DT*RINT;
            if(F2==0)
            {
                IROF=0;
                DF=RINT*DT;
                CUMF=CUMF+DF;
                return DF ;
            }
            R2=-XKF*SZF*(CD+F2)/(1-exp(SZF*F2));
            if(R2>RINT)
            {
                IROF=0;
                DF=RINT*DT;
                CUMF=CUMF+DF;
                return DF ;
            }
            F=CUMF+R2*DF;
            for(int I=1; I<=20; I++)
            {
                R2=-XKF*SZF*(CD+F)/(1-exp(SZF*F));
                if(R2>RINT)
                {
                    F1=F;
                    F=(F2+F)*0.5;
                    if(fabs(F-F1)<E)
                    {
                        TP=(IT-1)*DT+(F-CUMF)/RINT;
                        if(TP>(IT*DT))
                        {
                            IROF=0;
                            DF = RINT*DT;
                            CUMF=CUMF+DF;
                            return DF;
                        }
                    }

                }
                else
                {
                    F2=F;
                    F=(F2+F)*0.5;
                    if(fabs(F-F2)<E)
                    {
                        TP=(IT-1)*DT+(F-CUMF)/RINT;
                        if(TP>IT*DT)
                        {
                            IROF=0;
                            DF = RINT*DT;
                            CUMF=CUMF+DF;
                            return DF ;
                        }
                    }
                }

            }


        }
        else
        {
            F1=CUMF;
            R2=-XKF*SZF*(CD+F1)/(1-exp(SZF*F1));
            if(R2<RINT)
            {
                TP=(IT-1)*DT;
                IROF=1;
                F=CUMF;
            }
        }
        CONST=0;
        FAC=1;
        FC=F+CD;
        for(int J=1; J<=10; J++)
        {

            FAC=FAC*J;
            ADD=pow((FC*SZF),J)/(J*FAC);
            CONST=CONST+ADD;
        }
        CONST=log(FC)-(log(FC)+CONST)/exp(SZF*CD);
        IROF=1;
        F=F+0.5*RINT*(IT*DT-TP);
    }
    FC=F+CD;
    SUM=0;
    FAC=1;
    for(int J=1; J<=10; J++)
    {
        FAC=FAC*J;
        ADD=pow((FC*SZF),J)/(J*FAC);
        SUM=SUM+ADD;
    }
    FUNC=-(log(FC)-(log(FC)+SUM)/exp(SZF*CD)-CONST)/(XKF*SZF)-(IT*DT-TP);
    DFUNC=(exp(SZF*F)-1)/(XKF*SZF*FC);
    DF=-FUNC/DFUNC;
    F=F+DF;
    if(fabs(DF)<E)
    {
        if(F<(CUMF+RINT))
        {
            DF=F-CUMF;
            CUMF=F;
            F=F+DF;
            return DF ;
        }
    }
    if(F<(CUMF+RINT))
    {
        DF=F-CUMF;
        CUMF=F;
        F=F+DF;
        return DF ;
    }
    IROF=0;//THERE IS NO PONDING IN THIS TIME STEP
    DF=RINT*DT;
    CUMF=CUMF+DF;
    return DF ;
}
