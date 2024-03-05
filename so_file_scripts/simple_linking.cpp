#include <torch/torch.h>
#include <torch/script.h>
#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <vector>
#include <math.h>
#include "json/json.h"

#define DEBUG

using namespace std;
using namespace torch::indexing;

typedef struct _tagNN_MODEL // 구성요소 - nn pt파일, json파일
{
    // 각각 2개씩 구성되어있는 이유는 pt 및 json 파일이 I, Q로 이원화 되어있기때문
    string pt_file[2];
    string json_file[2]; 
} my_mosfet;
constexpr int model_max = 100; // 내부에서 가질 모델의 개수는 100개로 제한
extern my_mosfet NN_arr[];
extern int curr_NN_max;

/* I post process function */
torch::Tensor my_Ipostprocess_tensor(at::Tensor preds, Json::Value root, bool is_nmos)
{
    double id_max, id_min;
    id_max = root["Id"]["max"];
    id_min = root["Id"]["min"];

    #ifdef DEBUG
        cout << "(debug) " << __func__ << ": Checking current parameters" << endl;
        cout << "(debug) " << __func__ << ": Id(min, max) - " << id_min << ", " << id_max << endl;
    #endif // DEBUG

    int sig = 2*is_nmos - 1;
    preds.index({"...", 0}) = preds.index({"...", 0}) * (id_max - id_min) + id_min;
    preds = preds.squeeze(1);
    preds = pow(10,preds)*sig;
    
    #ifdef DEBUG
        cout << "(debug) " << __func__ << ": first elements of Id " << preds[0] << endl;
    #endif // DEBUG
    
    return preds;
}

torch::Tensor my_Qpostprocess_tensor(at::Tensor preds, Json::Value root)
{
    double Qd_max, Qd_min;
    double Qg_max, Qg_min;
    double Qb_max, Qb_min;
    Qd_max = root["Qd"]["max"];
    Qd_min = root["Qd"]["min"];
    Qg_max = root["Qg"]["max"];
    Qg_min = root["Qg"]["min"];
    Qb_max = root["Qb"]["max"];
    Qb_min = root["Qb"]["min"];

    #ifdef DEBUG
        cout << "(debug) " << __func__ << ": Checking Charge parameters " << endl;
        cout << "(debug) " << __func__ << ": Qd(min,max): " << Qd_min << ", " << Qd_max << endl;
        cout << "(debug) " << __func__ << ": Qg(min,max): " << Qg_min << ", " << Qg_max << endl;
        cout << "(debug) " << __func__ << ": Qb(min,max): " << Qb_min << ", " << Qb_max << endl;
    #endif // DEBUG

    preds.index({"...", 0}) = preds.index({"...", 0}) * (Qd_max - Qd_min) + Qd_min; // Qd
    preds.index({"...", 1}) = preds.index({"...", 1}) * (Qg_max - Qg_min) + Qg_min; // Qg
    preds.index({"...", 2}) = preds.index({"...", 2}) * (Qb_max - Qb_min) + Qb_min; // Qb

    #ifdef DEBUG
        cout << "(debug) " << __func__ << ": first elements of [Qd, Qg, Qb] " << preds[0][0]<< ", " << preds[0][1] << ", " << preds[0][2] << endl;
    #endif // DEBUG
    return preds;
}

int init_setting(const char* ){
    return id;
}

double my_infer(double vds, double vgs, double vbs, int output_id){
    /*
        Goal: 
            - Vds, Vgs, Vbs를 받아와 적절한 NN 모델의 연산 
            - 후처리 진행후 spice에 그 결과를 전달한다 
    */
    if (output_id == 0){ // I model

    }else if (output_id >= 1 && output_id <= 3){ // Q model

    }else{ // 에러
        cerr << __func__ << ": you give wrong output_id. Check this value(output_id): " << output_id << endl;
        return;
    }
    return val;
}