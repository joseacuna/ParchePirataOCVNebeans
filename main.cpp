/* 
 * File:   main.cpp
 * Author: slenderman
 *
 * Created on 24 de noviembre de 2013, 09:51 PM
 */

#include <cstdlib>

using namespace std;

/*
 * 
 */
//int main(int argc, char** argv) {
//
//    return 0;
//}

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
        float EYE_SX = 0.16f;
        float EYE_SY = 0.26f;
        float EYE_SW = 0.30f;
        float EYE_SH = 0.28f;
    
        Mat dest, gray;
      
   //string urlImagen="/home/slenderman/ProyectosGitHub/ParchePirataOCVNebeans/Fotos/diego.jpeg";
  string urlImagen="/home/slenderman/ProyectosGitHub/ParchePirataOCVNebeans/Fotos/cara01.jpg";
  //string urlImagen="/home/slenderman/ProyectosGitHub/ParchePirataOCVNebeans/Fotos/house.jpg";
    //string urlImagen="/home/slenderman/ProyectosGitHub/ParchePirataOCVNebeans/Fotos/cara02.jpg";
    Mat src=imread(urlImagen);
     //Mat src=imread("/Users/Diogo/Pictures/DSC03134.JPG");
    Mat imagen;
   
    
    
    Size sizeScr=src.size();
    cout<<"Ancho : "<<sizeScr.width<<"| Largo : "<<sizeScr.height<<endl;
    //resize(src,src, Size(800,600));
   
//    if (sizeScr.width<sizeScr.height) {
//        cout<<"Es mayor el Largo"<<endl;
//        resize(src,src, Size(800,600));
//        
//       transpose(src, imagen);
//       flip(imagen, imagen, 1);// refleja la imagen
//       
//        imwrite("imagen90grados.jpeg", imagen);
//        
//        
//    }
//    else{
    if(sizeScr.width>sizeScr.height){
        if(sizeScr.width>1024 || sizeScr.height>900){
            resize(src,src, Size(640,480));
            imagen=src;
        }
        else{
            if(sizeScr.width<1024 || sizeScr.height<900){
            resize(src,src, Size(640,480));
            imagen=src;
                }
                else{
             imagen=src;
        }
        }
       
    }else{
        if(sizeScr.width < sizeScr.height){
              if(sizeScr.width>1024 || sizeScr.height>900){
            resize(src,src, Size(300,400));
            imagen=src;
        }
        else{
            if(sizeScr.width<1024 || sizeScr.height<900){
            resize(src,src, Size(300,400));
            imagen=src;
                }
                else{
             imagen=src;
        }
        }
        }else{
            if(sizeScr.width > 400){
        resize(src,src, Size(300,400));
            imagen=src;
            }else{
            imagen=src;
            }
    }
    }
    
    
  
    //Mat imagen=imread("/Users/Diogo/Desktop/antonia2.jpg");
   // Mat imagen=imread("/Users/Diogo/Desktop/antonia2.jpg");
    
   // Mat imagenOriginal=imread("/Users/Diogo/Pictures/IMG_1957.JPG");
   // Mat imagen ;
    
    /*
    cout<<imagenOriginal.size()<<endl;
    resize(imagenOriginal, imagen, Size(440,440));
    cout<<imagen.size()<<endl;
*/

    
        CascadeClassifier detector, eyes_detector;
    
        if(!detector.load("/home/slenderman/ProyectosGitHub/ParchePirataOCVNebeans/haarcascades/haarcascade_frontalface_alt2.xml"))
                cout << "No se puede abrir clasificador." << endl;
    
        if(!eyes_detector.load("/home/slenderman/ProyectosGitHub/ParchePirataOCVNebeans/haarcascades/haarcascade_eye_tree_eyeglasses.xml"))
                cout << "No se puede abrir clasificador para los ojos." << endl;
    
        cvtColor(imagen, gray, CV_BGR2GRAY);
        equalizeHist(gray, dest);
    
        vector<Rect> rect;
        detector.detectMultiScale(dest, rect);
    
//        for(Rect rc : rect)
//        {
//        /*
//                rectangle(imagen,
//                  Point(rc.x, rc.y),
//                  Point(rc.x + rc.width, rc.y + rc.height),
//                  CV_RGB(0,255,0), 2);
//         */
//        
//        }
    
        if(rect.size() > 0)
        {
                Mat face = dest(rect[0]).clone();
                vector<Rect> leftEye, rightEye;
        
                int leftX = cvRound(face.cols * EYE_SX);
                int topY = cvRound(face.rows * EYE_SY);
                int widthX = cvRound(face.cols * EYE_SW);
                int heightY = cvRound(face.rows * EYE_SH);
                int rightX = cvRound(face.cols * (1.0-EYE_SX-EYE_SW));
        
                Mat topLeftOfFace = face(Rect(leftX, topY, widthX, heightY));
                Mat topRightOfFace = face(Rect(rightX, topY, widthX, heightY));
        
                eyes_detector.detectMultiScale(topLeftOfFace, leftEye);
                eyes_detector.detectMultiScale(topRightOfFace, rightEye);
        
                if((int)leftEye.size() > 0)
                {
            /*
                        rectangle(imagen,
                      Point(leftEye[0].x + leftX + rect[0].x, leftEye[0].y + topY + rect[0].y),
                      Point(leftEye[0].width + widthX + rect[0].x - 5, leftEye[0].height + heightY + rect[0].y),
                      CV_RGB(0,255,255), 2);
             */
                }
        
                if((int)rightEye.size() > 0)
                {
         
          //circulo del parche negro
            
            for (int i=0; i<rightEye[0].width/2+15; i++) {
                Point centerEyeRigth=Point(rightEye[0].x + rightX + rect[0].x+5, rightEye[0].y + topY + rect[0].y+rightEye[0].height/2);
                
                circle(imagen, centerEyeRigth, i, CV_RGB(0,0,0));
                
            }
            
        //  linea del tirante del parche
            Point puntoCentroParche=Point(rightEye[0].x + rightX + rect[0].x, rightEye[0].y + topY + rect[0].y+rightEye[0].height/2);
            Point puntoArriba=Point(rect[0].x+rect[0].width/2,rect[0].y);
            Point puntoDerecha=Point(rect[0].x+rect[0].width,rect[0].y+rect[0].height/2);
            line(imagen, puntoArriba, puntoCentroParche, CV_RGB(0, 0, 0));
            line(imagen, puntoDerecha, puntoCentroParche, CV_RGB(0, 0, 0));
            
          
            
        
          //circulo rojo
        Point centerEyeRigth2=Point(rightEye[0].width + widthX + rect[0].x + 5, rightEye[0].height + heightY + rect[0].y);
            //cout<<"Punto 2 :"<<centerEyeRigth2<<endl;
            circle(imagen, centerEyeRigth2, 5, CV_RGB(255, 0, 0));
            
            /*
                        rectangle(imagen,
                      Point(rightEye[0].x + rightX + leftX + rect[0].x, rightEye[0].y + topY + rect[0].y),
                      Point(rightEye[0].width + widthX + rect[0].x + 5, rightEye[0].height + heightY + rect[0].y),
                      CV_RGB(0,255,255), 2);
             
             */
                } 
        }
    
        imshow("Parche de Pirata", imagen);
        
        waitKey(0);
        return 1;
}

/*


 cout<<"rightEye[0].x :"<<rightEye[0].x <<"|rightX " <<rightX  <<"|leftX " <<leftX  <<"|rect[0].x :" <<rect[0].x <<endl<<"|rightEye[0].y :"<<rightEye[0].y <<"|topY :"<<topY<<"|rect[0].y :"<<rect[0].y<<endl<<endl;
 cout<<"rightEye[0].width :"<<rightEye[0].width <<"|widthX : " <<widthX <<"|rect[0].x+5 " <<rect[0].x+5<<endl<<"|rightEye[0].height :"<<rightEye[0].height<<"|heightY :"<<heightY<<"|rect[0].y :"<<rect[0].y<<endl<<endl;
 cout<<"Punto 1 :"<<centerEyeRigth<<endl;
 


*/