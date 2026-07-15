import tkinter as tk
from tkinter import ttk, messagebox
import json
import os
#Please ensure UTF-8 encoding is used to guarantee proper display of Chinese.
# 数据文件
DATA_FILE = os.path.join(os.path.dirname(__file__), "wrong_data.json")

# 初始化数据
if not os.path.exists(DATA_FILE):
    with open(DATA_FILE, "w", encoding="utf-8") as f:
        json.dump([], f, ensure_ascii=False, indent=2)

def load_data():
    with open(DATA_FILE, "r", encoding="utf-8") as f:
        return json.load(f)

def save_data(data):
    with open(DATA_FILE, "w", encoding="utf-8") as f:
        json.dump(data, f, ensure_ascii=False, indent=2)

# 主窗口
root = tk.Tk()
root.title("智能错题本小程序 - 刘佩霖")
root.geometry("750x550")

# 选项卡
tab = ttk.Notebook(root)
tab_add = ttk.Frame(tab)
tab_show = ttk.Frame(tab)
tab_practice = ttk.Frame(tab)
tab_stats = ttk.Frame(tab)

tab.add(tab_add, text="添加错题")
tab.add(tab_show, text="查看错题")
tab.add(tab_practice, text="错题练习")
tab.add(tab_stats, text="数据统计")
tab.pack(expand=1, fill="both")

# ====================== 1. 添加错题 ======================
tk.Label(tab_add, text="科目：", font=("黑体", 12)).place(x=30, y=30)
sub_var = tk.StringVar()
sub_entry = ttk.Combobox(tab_add, textvariable=sub_var, values=["数学", "语文", "英语", "物理", "道法", "历史","地理","生物","化学"])
sub_entry.place(x=100, y=30, width=150)

tk.Label(tab_add, text="题目：", font=("黑体", 12)).place(x=30, y=80)
q_entry = tk.Text(tab_add, width=60, height=3)
q_entry.place(x=100, y=80)

tk.Label(tab_add, text="我的答案：", font=("黑体", 12)).place(x=30, y=150)
my_entry = tk.Entry(tab_add, font=("黑体", 11))
my_entry.place(x=120, y=150, width=200)

tk.Label(tab_add, text="正确答案：", font=("黑体", 12)).place(x=30, y=190)
ans_entry = tk.Entry(tab_add, font=("黑体", 11))
ans_entry.place(x=120, y=190, width=200)

tk.Label(tab_add, text="错误原因：", font=("黑体", 12)).place(x=30, y=230)
reason_var = tk.StringVar()
reason_cb = ttk.Combobox(tab_add, textvariable=reason_var, values=["不会做", "粗心", "审题错误", "概念不清", "计算错误"])
reason_cb.place(x=120, y=230, width=170)

def add_wrong():
    sub = sub_var.get().strip()
    q = q_entry.get("1.0", tk.END).strip()
    my = my_entry.get().strip()
    ans = ans_entry.get().strip()
    reason = reason_var.get().strip()
    if not all([sub, q, my, ans, reason]):
        messagebox.showwarning("提示", "请把信息填完整！")
        return
    data = load_data()
    data.append({
        "subject": sub,
        "question": q,
        "my_ans": my,
        "right_ans": ans,
        "reason": reason
    })
    save_data(data)
    messagebox.showinfo("成功", "错题已保存！")
    sub_entry.delete(0, tk.END)
    q_entry.delete("1.0", tk.END)
    my_entry.delete(0, tk.END)
    ans_entry.delete(0, tk.END)
    reason_cb.delete(0, tk.END)
    show_all()
    update_stats()

tk.Button(tab_add, text="保存错题", font=("黑体", 12), bg="#409eff", fg="white", command=add_wrong).place(x=100, y=280, width=120)

# ====================== 2. 查看错题 ======================
tree = ttk.Treeview(tab_show, columns=("sub", "q", "my", "ans", "reason"), show="headings", height=15)
tree.heading("sub", text="科目")
tree.heading("q", text="题目")
tree.heading("my", text="我的答案")
tree.heading("ans", text="正确答案")
tree.heading("reason", text="错误原因")
tree.column("sub", width=80)
tree.column("q", width=280)
tree.column("my", width=100)
tree.column("ans", width=100)
tree.column("reason", width=120)
tree.place(x=10, y=10)

def show_all():
    for i in tree.get_children():
        tree.delete(i)
    data = load_data()
    for item in data:
        tree.insert("", tk.END, values=(
            item["subject"], item["question"][:20]+"..." if len(item["question"])>20 else item["question"],
            item["my_ans"], item["right_ans"], item["reason"]
        ))

tk.Label(tab_show, text="筛选科目：").place(x=30, y=400)
filter_sub = tk.StringVar()
filter_cb = ttk.Combobox(tab_show, textvariable=filter_sub, values=["全部", "数学", "语文", "英语", "物理", "道法", "历史", "地理", "生物", "化学"])
filter_cb.place(x=120, y=400)
filter_cb.current(0)

def filter_data():
    s = filter_sub.get()
    for i in tree.get_children():
        tree.delete(i)
    data = load_data()
    for item in data:
        if s == "全部" or item["subject"] == s:
            tree.insert("", tk.END, values=(
                item["subject"], item["question"][:20]+"..." if len(item["question"])>20 else item["question"],
                item["my_ans"], item["right_ans"], item["reason"]
            ))

tk.Button(tab_show, text="筛选", command=filter_data).place(x=280, y=400)
show_all()

# ====================== 3. 错题练习 ======================
def practice():
    data = load_data()
    if not data:
        messagebox.showinfo("提示", "先录入错题再练习！")
        return
    p_win = tk.Toplevel(tab_practice)
    p_win.title("错题练习")
    p_win.geometry("600x400")
    idx = 0
    def show_one():
        nonlocal idx
        if idx >= len(data):
            messagebox.showinfo("完成", "已练完全部错题！")
            p_win.destroy()
            return
        item = data[idx]
        for w in p_win.winfo_children():
            w.destroy()
        tk.Label(p_win, text=f"科目：{item['subject']}", font=("黑体", 13)).pack(pady=5)
        tk.Label(p_win, text="题目："+item['question'], wraplength=550, justify="left", font=("黑体", 12)).pack(pady=5)
        tk.Label(p_win, text="请输入正确答案：").pack()
        e = tk.Entry(p_win, font=("黑体", 12))
        e.pack(pady=5)
        def check():
            nonlocal idx
            u = e.get().strip()
            if u == item['right_ans']:
                messagebox.showinfo("正确", "太棒了！")
            else:
                messagebox.showwarning("错误", f"正确答案：{item['right_ans']}\n原因：{item['reason']}")
            idx += 1
            show_one()
        tk.Button(p_win, text="提交答案", command=check).pack(pady=10)
    show_one()

tk.Button(tab_practice, text="开始错题练习", font=("黑体", 14), bg="#67c23a", fg="white", command=practice).pack(pady=50)

# ====================== 4. 数据统计 ======================
stats_label = tk.Label(tab_stats, text="", font=("黑体", 14), justify="left")
stats_label.place(x=50, y=50)

def update_stats():
    data = load_data()
    total = len(data)
    sub_count = {}
    reason_count = {}
    for item in data:
        s = item["subject"]
        r = item["reason"]
        sub_count[s] = sub_count.get(s, 0) + 1
        reason_count[r] = reason_count.get(r, 0) + 1
    text = f"总错题数：{total}\n\n各科目错题数量：\n"
    for k, v in sub_count.items():
        text += f"• {k}：{v} 题\n"
    text += "\n错误原因统计：\n"
    for k, v in reason_count.items():
        text += f"• {k}：{v} 次\n"
    stats_label.config(text=text)

update_stats()

root.mainloop()
