import ctypes
import os
import time

def main():
    # 1. 加载 C++ 编译好的 DLL
    dll_path = os.path.abspath("random_algorithm.dll")
    if not os.path.exists(dll_path):
        print(f"找不到 {dll_path}，请先编译 C++ 文件！")
        return

    my_lib = ctypes.CDLL(dll_path)
    my_lib.init_random.argtypes = [ctypes.c_int, ctypes.c_int]
    my_lib.generate_random.restype = ctypes.c_int

    # 2. 初始化题库
    min_num = int(input("请输入抽号范围的最小值："))
    max_num = int(input("请输入抽号范围的最大值："))
    my_lib.init_random(min_num, max_num)

    print("====================================")
    print(f"抽号系统已就绪 (范围: {min_num} - {max_num})")
    print("规则：每次抽取1个，并随机拿掉另外1个，剩余数字概率提升2%")
    print("====================================\n")

    round_count = 1
    while True:
        # 等待用户按键（直接按回车即可）
        user_input = input(f"👉 第 {round_count} 次抽取，请按 [Enter] 键开始 (或输入 q 退出)：")
        
        if user_input.strip().lower() == 'q':
            print("退出抽号系统。")
            break

        print("正在抽取中...")
        time.sleep(0.5) # 加一点小延迟，营造悬念感

        # 调用 C++ 核心算法
        result = my_lib.generate_random()

        if result == -1:
            input("已经空了，无法继续抽取！")
            break

        # 3. 展示结果（这里展示的是两个被拿走的数字中的“正牌抽中结果”）
        print(f"抽中的号是：【第 {result} 号】")
        print(f"（系统已自动将第 {result} 号和另一个随机号从号库中移除，剩余号码概率已提升 2%）\n")
        print("-" * 40)

        round_count += 1

if __name__ == "__main__":
    main()