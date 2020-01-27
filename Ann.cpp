/*
181312018--BAHTIYAR KARAKOC
181312060--BEYZA KALCI

SIMPLE NEURAL NET DENEMESI
*/


#include <iostream>
#include <cstdlib>
#include <math.h>
#include <time.h>
#include <windows.h>
#include "Renk.h"//ciktilari renkli gostermek icin header.gerekli degildi ama estetik ve anlasilir oldu.
#pragma commeint(lib, "user32")
using namespace std;
double Sigmoid(double x){//sigmoid Fonksiyonu
    return 1/(1+exp(-x));
}
double Tur_Sig(double x){//sigmoid Fonksiyonunun Turevi
    return x*(1-x);
}
class Synaptic{//Yapay Sinir Agimizin Sinapsis Sinifi
    private:
        //double IValue;//Sinaps Degeri.
        double Size_W;//Sinaps icin Olusturulan dizinin Boyutu;
        double Size_Fv;//Atesleme degeri Boyutu;
    public:
        double FireValue;//Atesleme Degeri.
        double *Weight;//Sinapsin Agirlik Degeri.
        double Data1;


        void SetWeight(double Data1,double NeuronImplement){
             srand(time(NULL));//Random Degerler Uretmek Icin.
             this -> Size_W = Data1;
             Weight = (double *)malloc(sizeof(double) * Size_W);//Dinamik olarak yer Weight Array'i Olusturuyoruz.
			 for(int i=1;i<=NeuronImplement;i++){

                Weight[i]=2.0*rand()/RAND_MAX-1;

                }
			 }

        Synaptic(){
            this -> Weight = 0;
            this -> FireValue  = 0;
        }
        ~Synaptic(){
            free(Weight);
        }
        //Synaptic(double,double);


        /*double Fire(){
			 return ;
        }*/
}sy1;

class Neuron:public Synaptic{//Noron Sinifi
    private:
        /*double *Before;//
         double *Now;anlik*/
        double Size_Bfi;//Input Matrisin Satir Boyutu.
        double Size_Bfj;//Input Matrisin Sutun Boyutu.
        double Size_Now;//Output array Boyutu.
    public:
        int Neuron_Implement;//Noron Layer Sayisi.
        int Neuron_Numbers;//Giris Sayisi.
        double *Forwards;//Noron Cikis Bilgisi.
        double *Incoming;//Noronun Giris Bilgisi.
        Neuron(){
            this -> Forwards = 0;
            this -> Incoming = 0;
        }
        void SetBefore(double Data_i,double Data_j,double Data_k){
        srand(time(NULL));//Random Degerler Uretmek Icin.
        this -> Size_Bfi = Data_i;
            this ->Size_Bfj = Data_j;
                this ->Size_Now =Data_k;
                    Incoming = (double *)malloc(Size_Bfi * Size_Bfj * sizeof(double));
                        Forwards = (double *)malloc(sizeof(double) * Size_Now);
                //Incoming = new double[Size_Bfi*Size_Bfj]; niye olmuyor arastir.
                    cout<<"Giris Katmaninin Noron Sayisini Giriniz: ";
                                cin>>Neuron_Implement;
                                    cout<<"\nKac Adet Sayi Girisi Yapilacak:";
                                        cin>>Neuron_Numbers;
                    cout<<"Sinaps Agirliginin Boyutunu Giriniz:";
                                    cin >>Data1;
                for(int i=0;i<Neuron_Numbers;i++){
                        cout<<"\n\n";
                        for(int j=0;j<Neuron_Implement;j++){
                                    cout<<"Input Girisi x["<<j+1<<"]:";
                                    cin>>Incoming[i*j+j];
                        }
                                        cout<<"Output Girisi y["<<i+1<<"]";
                                            cin>>Forwards[i];
                }
                SetWeight(Data1,Neuron_Implement);

        }
        /*~Neuron(){
            free(Forwards);
            free(Incoming);
        }*/

}a1;

class Layer:public Neuron{//Katman Sinifi
    private:
        double Size_Layer;
    public:
            double *Layer1;

                Layer(){
                    this -> Layer1 = 0;
                }
        void SetLayer(double Data){
            srand(time(NULL));//Random Degerler Uretmek Icin.
                this ->Size_Layer = Data;
                Layer1 =(double *)malloc(sizeof(double)*Size_Layer);

        }

        ~Layer(){
            free(Layer1);
        }

};

class Ann:public Layer{//Ann(Artificial Neural Network) = Yapay Sinir Agi Sinifi
        private:
            double Error;//Hata Degiskeni.
            double Temp;//Gecici Desgisken.
            double Alpha;//Adim Sayisi.
            double Input_i,Input_j;
            double Output_i;
            double Layer_i;
            int Secim;
        public:
        int i,j,k;
            void Set_Ann(){

                    cout<<"Input Katmaninin [i]ve[j] Boyut Girisini Yapiniz:";
                    cin>>Input_i;cin>>Input_j;
                    cout<<"Output [i] Boyut Girisi Yapiniz:"<<endl;
                    cin>>Output_i;
                    cout<<"Layer Boyut Girisini Yapiniz:"<<endl;
                    cin>>Layer_i;
                    SetLayer(Layer_i);
            }
            void Get_Ann(){
                srand(time(NULL));//Random Degerler Uretmek Icin.
                Set_Ann();
                SetBefore(Input_i,Input_j,Output_i);//Noron Gelen Bilgi Boyut Girisi
                for(i=0;;i++){
                        Error=0;
                            for(j=0;j<Neuron_Numbers;j++){
                                        Temp=0;
                                            for(k=0;k<Neuron_Implement;k++){
                                                    Temp+=Incoming[j*k+k]*Weight[k];
                                            }
                                Layer1[j]=Sigmoid(Temp);

                                          Error+=fabs(Layer1[j]-Forwards[j]);
                                          Layer1[j]=(Layer1[j]-Forwards[j]*Tur_Sig(Layer1[j]));
                                          /*
                                          
                                          bu kisimda matrisin transpozunu hesaplarken bir islem hatası
                                          var sebebi bence dinamik bellegi dogru kullanamamamız.
                                          eger buradaki sorun cozulurse kod tamamen dogru ve eksiksiz calisacaktir.

                                          
                                          */


                            }

                                        for(j=1;j<Neuron_Implement;j++){

                                                            Temp=0;
                                                                for(k=1;k<Neuron_Numbers;k++){

                                                                        Temp+=Incoming[k*j+j]*Layer1[k];
                                                                }
                                                    Weight[j]-=Alpha*Temp;

                                        }

            if(i==100000){

                i=0; cout<<red<<"\n Error(Hata):"<<Error<<yellow<<"  Weight(Agirlik):"<<Weight[1]<<endl;
                                            }


            if(GetAsyncKeyState(VK_ESCAPE)){
				break;

                                }
                        }
                        Test_Case();
            }
            void Print_Weight_Sinaps(){
                for(i=0;i<Neuron_Implement;i++){
                    cout<<"W["<<i<<"]:"<<Weight[i]<<endl;
                }
            }
        void Test(){
            double S,I;
            cout<<"Test Degerini Giriniz: "<<endl;
            S=0;
            for(i=0;i<Neuron_Implement;i++){
                cout<<"Test Noron Girisi[x]:"<<endl;
                cin>>I;
                S+=I*Weight[i];
            }
            cout<<"Outuput Degeri: "<<Sigmoid(S)<<endl;

        }
        void Test_Case(){
            while(Secim!=4){


            cout<<"[1] Test"<<endl;
            cout<<"[2] Sinaps Agirligi"<<endl;
            cout<<"[3] Ogrenme Oranini Kontrol Et"<<endl;
            cout<<"[4] Cikis"<<endl;
            cout<<"Secim Yapiniz:";
            cin>>Secim;
            switch (Secim)
            {
            case 1:
                    Test();
                break;
            case 2:
                        Print_Weight_Sinaps();
                break;
            case 3:
                    cout<<"Alpha: "<<Alpha<<endl;
                    cout<<"\n\n"; break;
            case 4: cout<<"Cikis Yapildi"<<endl; break;
            default:
                break;
            }
        }
        }

        Ann(){
                    Alpha = 1;
        }


}Neu1;
int main(int argc, char const *argv[]){
::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
        Neu1.Get_Ann();


    return 0;
}
