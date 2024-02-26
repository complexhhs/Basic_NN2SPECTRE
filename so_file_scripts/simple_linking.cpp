#include <torch/torch.h>
#include <torch/script.h>
#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <vector>
#include <math.h>
#include "json/json.h"

using namespace std;
using namespace torch::indexing;

/* I post process function */
torch::Tensor my_Ipostprocess_tensor(at::Tensor preds, Json::Value root, bool is_nmos)
{
    double id_max, id_min;
    id_max = root["Id"]["max"];
    id_min = root["Id"]["min"];

    int sig = 2*is_nmos - 1;
    preds.index({"...", 0}) = preds.index({"...", 0}) * (id_max - id_min) + id_min;
    preds = preds.squeeze(1);
    preds = pow(10,preds)*sig;
    return preds;
}

torch::Tensor my_Qpostprocess_tensor(at::Tensor preds, string json_filename)
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

    preds.index({"...", 0}) = preds.index({"...", 0}) * (Qd_max - Qd_min) + Qd_min // Qd
    preds.index({"...", 1}) = preds.index({"...", 1}) * (Qg_max - Qg_min) + Qg_min // Qg
    preds.index({"...", 2}) = preds.index({"...", 2}) * (Qb_max - Qb_min) + Qb_min // Qb
    return preds;
}

int init_setting()