// C107110257_hw03_laplacian_image_enhancement.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include "myHist.h"

int main()
{

    myHist* pHist = new myHist(myHist::Type::Image);

    int  neighbor[9][2] = { {-1,-1}, { 0,-1}, {+1,-1},
                            {-1, 0}, { 0, 0}, {+1, 0},
                            {-1,+1}, { 0,+1}, {+1,+1} };
    
    float pxA = 1.3, weight[9] = { 0.0,-1.0,0.0,   -1.0,5.0,-1.0,    0.0,-1.0,0.0 },//laplacian,
                     weight2 = 4.0;//laplacian_high_boost
    int mode = 1;//1=laplacian, 2=laplacian_high_boost
    cv::Mat m_out, m_in = cv::imread("lena.bmp", 0);

    int R = m_in.rows,
        C = m_in.cols,
        matrix_size = 9;

    m_out.create(R, C, CV_8UC1);

    for (int r = 1; r < R - 1; r++)
        for (int c = 1; c < C - 1; c++) {
            float sum = 0.0;
            for (int i = 0; i < matrix_size; i++) {
                int mr = r + neighbor[i][1];
                int mc = c + neighbor[i][0];
                if (mode == 2 && i == matrix_size / 2)
                    sum += m_in.at<uchar>(mr, mc) * (weight2 + pxA);
                else
                    sum += m_in.at<uchar>(mr, mc) * weight[i];
            }// End of for(m)
            if (sum > 255)
                sum = 255.0;
            else if (sum < 0)
                sum = 0.0;
            m_out.at<uchar>(r, c) = int(sum);
        }
    // ################################################m_in picture and hist show
    cv::namedWindow("Lena_before", cv::WINDOW_AUTOSIZE);
    cv::imshow("Lena_before", m_in);
    //---------------------------------------
    pHist->CalcHist(m_in);
    m_in = cv::Scalar::all(0);
    pHist->Show(m_in);
    cv::namedWindow("intput hist", cv::WINDOW_AUTOSIZE);
    cv::imshow("intput hist", m_in);
    pHist->Clear();
    // ################################################m_out picture and hist show
    cv::namedWindow("Lena_after", cv::WINDOW_AUTOSIZE);
    cv::imshow("Lena_after", m_out);
    //---------------------------------------
    pHist->CalcHist(m_out);
    m_out = cv::Scalar::all(0);
    pHist->Show(m_out);
    cv::namedWindow("output hist", cv::WINDOW_AUTOSIZE);
    cv::imshow("output hist", m_out);
    pHist->Clear();


    cv::waitKey(0);
    return 0;
}
// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
