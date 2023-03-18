// C107110257_hw03_media_filter.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include "myHist.h"
int QuickSort(int *A, int left, int right)
{
    int i, j, s, Temp;
    if (left < right) {
        s = A[(left + right) / 2];
        i = left - 1;
        j = right + 1;
        while (1) {
            while (A[++i] < s);  // 向右找
            while (A[--j] > s);  // 向左找
            if (i >= j) break;
            Temp = A[i];
            A[i] = A[j];
            A[j] = Temp;
        }
        QuickSort(A, left, i - 1);   // 對左邊進行遞迴
        QuickSort(A, j + 1, right);  // 對右邊進行遞迴
    }
    return A[9];
}
int main()
{
    myHist* pHist = new myHist(myHist::Type::Image);

    cv::Mat m_in = cv::imread("lena.bmp", 0);

    int R = m_in.rows,
        C = m_in.cols,
        matrix_size = 9,
        v_temp[9] = { 0 },
        neighbor[9][2] = { {-1,-1}, { 0,-1}, {+1,-1},
                           {-1, 0}, { 0, 0}, {+1, 0},
                           {-1,+1}, { 0,+1}, {+1,+1} };

    cv::Mat m_out;
    m_out.create(R, C, CV_8UC1);

    for (int r = 1; r < R - 1; r++)
        for (int c = 1; c < C - 1; c++) {
            float sum = 0.0;
            for (int i = 0; i < matrix_size; i++) {
                int mr = r + neighbor[i][1];
                int mc = c + neighbor[i][0];
                v_temp[i] = m_in.at<uchar>(mr, mc);
            }
            QuickSort(v_temp, 0, matrix_size - 1);
            for (int i = 0; i < matrix_size; i++) {
                int mr = r + neighbor[i][1];
                int mc = c + neighbor[i][0];
                m_out.at<uchar>(mr, mc) = v_temp[matrix_size / 2];
            }
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
