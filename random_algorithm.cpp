#include <cstdlib>
#include <ctime>

static double weights[10000]; 
static int current_min = 0;
static int current_max = 0;

extern "C" {
    // 初始化题库
    __declspec(dllexport) void init_random(int min_val, int max_val) {
        current_min = min_val;
        current_max = max_val;
        for (int i = min_val; i <= max_val; i++) {
            weights[i] = 100.0; 
        }
        srand((unsigned)time(NULL));
    }

    // 核心抽取函数（包含你的4步规则循环）
    __declspec(dllexport) int generate_random() {
        // 【第1步：抽取】
        double total_weight = 0.0;
        for (int i = current_min; i <= current_max; i++) {
            total_weight += weights[i];
        }
        if (total_weight <= 0.0) return -1; 

        double rand_val = ((double)rand() / RAND_MAX) * total_weight;
        double current_weight = 0.0;
        int selected_number = -1;
        
        for (int i = current_min; i <= current_max; i++) {
            current_weight += weights[i];
            if (rand_val <= current_weight && weights[i] > 0) {
                selected_number = i;
                break;
            }
        }

        // 【第2步：移除自己】
        if (selected_number != -1) {
            weights[selected_number] = 0.0; 
        }

        // 【第3步：移除另外一个随机数字】
        double total_weight_after = 0.0;
        for (int i = current_min; i <= current_max; i++) {
            total_weight_after += weights[i];
        }

        // 安全判断：如果题库里还有剩余数字，才执行移除
        if (total_weight_after > 0.0) {
            double rand_val_after = ((double)rand() / RAND_MAX) * total_weight_after;
            double current_weight_after = 0.0;
            for (int i = current_min; i <= current_max; i++) {
                current_weight_after += weights[i];
                if (rand_val_after <= current_weight_after && weights[i] > 0) {
                    weights[i] = 0.0; // 移除第二个数字
                    break; 
                }
            }
        }

        // 【第4步：剩余数字概率 +2%】
        for (int i = current_min; i <= current_max; i++) {
            if (weights[i] > 0) {
                weights[i] *= 1.02; 
            }
        }

        // 返回第一步抽中的号码，循环结束
        return selected_number;
    }
}