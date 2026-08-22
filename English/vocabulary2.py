import json
import random
import tkinter as tk
from tkinter import ttk, messagebox, simpledialog, scrolledtext
from PIL import Image, ImageTk
import os
from collections import defaultdict
import datetime
import math

# 单词库文件名
WORD_FILE = "vocabulary2.json"
MISTAKE_FILE = "mistake_counts.json"
RATING_FILE = "rating_history.json"
USER_DATA_FILE = "user_data.json"
BACKGROUND_COLOR = "#F0F8FF"
ACCENT_COLOR = "#4682B4"
BUTTON_COLOR = "#5F9EA0"
HIGHLIGHT_COLOR = "#87CEEB"

class VocabularyApp:
    def __init__(self, root):
        self.root = root
        self.root.title("单词听写系统")
        self.root.geometry("900x600")
        self.root.configure(bg=BACKGROUND_COLOR)
        
        # 创建单词库文件如果不存在
        if not os.path.exists(WORD_FILE):
            with open(WORD_FILE, 'w', encoding='utf-8') as f:
                json.dump({}, f, ensure_ascii=False, indent=2)
        
        # 创建错误计数文件如果不存在
        if not os.path.exists(MISTAKE_FILE):
            with open(MISTAKE_FILE, 'w', encoding='utf-8') as f:
                json.dump({}, f, ensure_ascii=False, indent=2)
        
        # 加载单词库
        self.vocab = self.load_vocabulary()
        
        # 加载错误计数
        self.mistake_counts = self.load_mistake_counts()
        
        # 创建样式
        self.create_styles()

        # 加载评级历史
        self.rating_history = self.load_rating_history()
        
        # 加载用户数据
        self.user_data = self.load_user_data()
        
        # 创建评级显示区域
        self.create_rating_display()
        
        # 创建界面
        self.create_widgets()
        
        # 更新单词库显示
        self.update_sections_list()
    
    def create_styles(self):
        """创建界面样式"""
        style = ttk.Style()
        style.configure("TFrame", background=BACKGROUND_COLOR)
        style.configure("Header.TLabel", background=ACCENT_COLOR, foreground="white", font=("Arial", 16, "bold"))
        style.configure("Section.TButton", background=BUTTON_COLOR, foreground="black", font=("Arial", 10))
        style.configure("Accent.TButton", background=ACCENT_COLOR, foreground="white", font=("Arial", 12, "bold"))
        style.configure("Listbox.TFrame", background="white", borderwidth=1, relief="sunken")
        style.configure("Result.TLabel", background=HIGHLIGHT_COLOR, foreground="black", font=("Arial", 12))
        style.configure("MistakeHeader.TLabel", background="#FFD700", foreground="black", font=("Arial", 12, "bold"))
        style.configure("Attempts.TLabel", background="#FFEC8B", foreground="black", font=("Arial", 10))
        style.configure("Progress.TLabel", background=BACKGROUND_COLOR, foreground="#4682B4", font=("Arial", 10, "bold"))
        style.configure("Hint.TLabel", background="#FFFACD", foreground="#8B4513", font=("Arial", 11))
    
    def create_widgets(self):
        """创建界面组件"""
        # 创建主框架
        main_frame = ttk.Frame(self.root, padding=20)
        main_frame.pack(fill=tk.BOTH, expand=True)
        
        # 标题
        header_frame = ttk.Frame(main_frame)
        header_frame.pack(fill=tk.X, pady=(0, 20))
        
        ttk.Label(header_frame, text="单词听写系统", style="Header.TLabel").pack(fill=tk.X, padx=10, pady=10)
        
        # 主内容区域
        content_frame = ttk.Frame(main_frame)
        content_frame.pack(fill=tk.BOTH, expand=True)
        
        # 左侧面板 - 单词库管理
        left_panel = ttk.Frame(content_frame, width=300)
        left_panel.pack(side=tk.LEFT, fill=tk.Y, padx=(0, 20))
        
        # 单词库列表
        sections_frame = ttk.LabelFrame(left_panel, text="单词库列表", padding=10)
        sections_frame.pack(fill=tk.BOTH, pady=(0, 20))
        
        self.sections_listbox = tk.Listbox(sections_frame, selectmode=tk.MULTIPLE, height=10, font=("Arial", 11))
        self.sections_listbox.pack(fill=tk.BOTH, expand=True)
        
        scrollbar = ttk.Scrollbar(sections_frame, orient=tk.VERTICAL, command=self.sections_listbox.yview)
        scrollbar.pack(side=tk.RIGHT, fill=tk.Y)
        self.sections_listbox.config(yscrollcommand=scrollbar.set)
        
        # 操作按钮
        btn_frame = ttk.Frame(left_panel)
        btn_frame.pack(fill=tk.X, pady=(0, 10))
        
        ttk.Button(btn_frame, text="添加单词", command=self.add_word_dialog, style="Section.TButton").pack(side=tk.LEFT, fill=tk.X, expand=True, padx=2)
        ttk.Button(btn_frame, text="删除单词", command=self.delete_word_dialog, style="Section.TButton").pack(side=tk.LEFT, fill=tk.X, expand=True, padx=2)
        
        # 添加/删除编号集合
        section_frame = ttk.Frame(left_panel)
        section_frame.pack(fill=tk.X, pady=(0, 20))
        
        ttk.Button(section_frame, text="添加集合", command=self.add_section_dialog, style="Section.TButton").pack(side=tk.LEFT, fill=tk.X, expand=True, padx=2)
        ttk.Button(section_frame, text="删除集合", command=self.delete_section_dialog, style="Section.TButton").pack(side=tk.LEFT, fill=tk.X, expand=True, padx=2)
        
        # 开始听写按钮
        ttk.Button(left_panel, text="开始听写", command=self.start_test, style="Accent.TButton").pack(fill=tk.X, pady=10)
        
        # 查看错误次数按钮
        ttk.Button(left_panel, text="查看错误次数", command=self.show_mistake_counts, style="Section.TButton").pack(fill=tk.X, pady=5)
        
        # 重置错误次数按钮
        ttk.Button(left_panel, text="重置错误次数", command=self.reset_mistake_counts, style="Section.TButton").pack(fill=tk.X, pady=5)
        
        # 右侧面板 - 测试区域
        right_panel = ttk.Frame(content_frame)
        right_panel.pack(side=tk.RIGHT, fill=tk.BOTH, expand=True)
        
        # 当前测试信息
        self.test_info = ttk.Label(right_panel, text="选择单词集合并点击'开始听写'按钮", font=("Arial", 12), background=BACKGROUND_COLOR)
        self.test_info.pack(fill=tk.X, pady=(0, 10))
        
        # 测试问题区域
        self.question_frame = ttk.LabelFrame(right_panel, text="单词听写", padding=10)
        self.question_frame.pack(fill=tk.BOTH, expand=True)
        
        # 进度显示区域
        self.progress_frame = ttk.Frame(self.question_frame)
        self.progress_frame.pack(fill=tk.X, pady=5)
        
        self.progress_label = ttk.Label(self.progress_frame, text="", style="Progress.TLabel")
        self.progress_label.pack(side=tk.RIGHT)
        
        self.question_label = ttk.Label(self.question_frame, text="请准备...", font=("Arial", 14, "bold"), background=BACKGROUND_COLOR)
        self.question_label.pack(pady=10)
        
        # 提示区域
        self.hint_frame = ttk.Frame(self.question_frame)
        self.hint_frame.pack(fill=tk.X, pady=5)
        
        self.hint_label = ttk.Label(self.hint_frame, text="", style="Hint.TLabel")
        self.hint_label.pack()
        
        # 尝试次数显示
        self.attempts_label = ttk.Label(self.question_frame, text="", style="Attempts.TLabel")
        self.attempts_label.pack(pady=5)
        
        self.answer_entry = ttk.Entry(self.question_frame, font=("Arial", 12))
        self.answer_entry.pack(fill=tk.X, pady=10)
        self.answer_entry.bind("<Return>", self.check_answer)
        
        self.feedback_label = ttk.Label(self.question_frame, text="", font=("Arial", 12), background=BACKGROUND_COLOR)
        self.feedback_label.pack(pady=5)
        
        # 按钮区域
        self.btn_frame = ttk.Frame(self.question_frame)
        self.btn_frame.pack(fill=tk.X, pady=10)
        
        self.check_btn = ttk.Button(self.btn_frame, text="检查", command=self.check_answer, style="Section.TButton")
        self.check_btn.pack(side=tk.LEFT, padx=5)
        
        self.skip_btn = ttk.Button(self.btn_frame, text="跳过", command=self.next_question, style="Section.TButton")
        # self.skip_btn.pack(side=tk.LEFT, padx=5)
        
        self.end_btn = ttk.Button(self.btn_frame, text="结束测试", command=self.end_test, style="Section.TButton")
        self.end_btn.pack(side=tk.RIGHT, padx=5)
        
        # 重新测试按钮（初始隐藏）
        self.retry_btn = ttk.Button(self.question_frame, text="重新测试", command=self.retry_test, style="Accent.TButton")
        
        # 测试结果区域
        self.result_frame = ttk.LabelFrame(right_panel, text="测试结果", padding=10)
        self.result_frame.pack(fill=tk.BOTH, pady=(10, 0))
        
        # 初始状态
        self.test_in_progress = False
        self.current_words = []  # 存储 (中文, 英文, 所属集合) 元组
        self.current_index = 0
        self.total_words = 0
        self.correct_count = 0
        self.wrong_count = 0
        self.current_sections = []
        self.wrong_words = []  # 存储错误的单词 (中文, 英文, 所属集合)
        self.current_attempts = 0  # 当前单词尝试次数
        self.current_word_correct = False  # 当前单词是否已答对
        self.current_hint_level = 0  # 当前提示级别
    
    def load_vocabulary(self):
        """加载单词库"""
        try:
            with open(WORD_FILE, 'r', encoding='utf-8') as f:
                return json.load(f)
        except (FileNotFoundError, json.JSONDecodeError):
            return {}
    
    def load_mistake_counts(self):
        """加载错误计数"""
        try:
            with open(MISTAKE_FILE, 'r', encoding='utf-8') as f:
                return json.load(f)
        except (FileNotFoundError, json.JSONDecodeError):
            return {}
    
    def save_vocabulary(self):
        """保存单词库"""
        with open(WORD_FILE, 'w', encoding='utf-8') as f:
            json.dump(self.vocab, f, ensure_ascii=False, indent=2)
    
    def save_mistake_counts(self):
        """保存错误计数"""
        with open(MISTAKE_FILE, 'w', encoding='utf-8') as f:
            json.dump(self.mistake_counts, f, ensure_ascii=False, indent=2)
    
    def update_sections_list(self):
        """更新单词库列表显示"""
        self.sections_listbox.delete(0, tk.END)
        for section in self.vocab:
            word_count = len(self.vocab[section])
            self.sections_listbox.insert(tk.END, f"集合 {section} ({word_count}个单词)")
    
    def add_section_dialog(self):
        """添加新的编号集合对话框"""
        section = simpledialog.askstring("添加集合", "请输入新的集合编号:", parent=self.root)
        if section and section.strip():
            section = section.strip()
            if section in self.vocab:
                messagebox.showwarning("集合已存在", f"集合 '{section}' 已经存在!")
            else:
                self.vocab[section] = {}
                self.save_vocabulary()
                self.update_sections_list()
                messagebox.showinfo("添加成功", f"集合 '{section}' 已创建!")
    
    def delete_section_dialog(self):
        """删除编号集合对话框"""
        selected = self.sections_listbox.curselection()
        if not selected:
            messagebox.showwarning("未选择", "请选择一个或多个集合!")
            return
        
        if messagebox.askyesno("确认删除", "确定要删除选中的集合吗？\n该操作不可恢复!"):
            sections_to_delete = []
            for index in selected:
                section = self.sections_listbox.get(index).split()[1]
                sections_to_delete.append(section)
            
            for section in sections_to_delete:
                if section in self.vocab:
                    del self.vocab[section]
                # 同时删除该集合的所有错误计数
                for chinese in list(self.mistake_counts.keys()):
                    if chinese in self.mistake_counts and section in self.mistake_counts[chinese]:
                        del self.mistake_counts[chinese][section]
            
            self.save_vocabulary()
            self.save_mistake_counts()
            self.update_sections_list()
            messagebox.showinfo("删除成功", f"已删除 {len(sections_to_delete)} 个集合!")
    
    def add_word_dialog(self):
        """添加单词对话框"""
        # 获取选中的集合
        selected = self.sections_listbox.curselection()
        if not selected:
            messagebox.showwarning("未选择", "请先选择一个集合!")
            return
        
        # 创建添加单词窗口
        add_window = tk.Toplevel(self.root)
        add_window.title("添加单词")
        add_window.geometry("400x300")
        add_window.transient(self.root)
        add_window.grab_set()
        
        # 获取选中的集合
        section = self.sections_listbox.get(selected[0]).split()[1]
        
        # 标题
        ttk.Label(add_window, text=f"添加到集合: {section}", font=("Arial", 12, "bold")).pack(pady=10)
        
        # 表单框架
        form_frame = ttk.Frame(add_window)
        form_frame.pack(fill=tk.BOTH, padx=20, pady=10)
        
        # 中文输入
        ttk.Label(form_frame, text="中文:").grid(row=0, column=0, sticky=tk.W, pady=5)
        chinese_entry = ttk.Entry(form_frame, width=30)
        chinese_entry.grid(row=0, column=1, sticky=tk.W, pady=5)
        chinese_entry.focus()
        
        # 英文输入
        ttk.Label(form_frame, text="英文:").grid(row=1, column=0, sticky=tk.W, pady=5)
        english_entry = ttk.Entry(form_frame, width=30)
        english_entry.grid(row=1, column=1, sticky=tk.W, pady=5)
        
        # 按钮框架
        btn_frame = ttk.Frame(add_window)
        btn_frame.pack(fill=tk.X, pady=10, padx=20)
        
        def save_word():
            chinese = chinese_entry.get().strip()
            english = english_entry.get().strip()
            
            if not chinese or not english:
                messagebox.showwarning("输入错误", "中文和英文都不能为空!")
                return
            
            if chinese in self.vocab[section]:
                if messagebox.askyesno("单词已存在", f"单词 '{chinese}' 已存在，是否覆盖?"):
                    self.vocab[section][chinese] = english
            else:
                self.vocab[section][chinese] = english
            
            # 初始化错误计数（如果不存在）
            if chinese not in self.mistake_counts:
                self.mistake_counts[chinese] = {}
            if section not in self.mistake_counts[chinese]:
                self.mistake_counts[chinese][section] = 0
            
            self.save_vocabulary()
            self.save_mistake_counts()
            self.update_sections_list()
            messagebox.showinfo("添加成功", f"已添加单词: {chinese} = {english}")
            add_window.destroy()
        
        ttk.Button(btn_frame, text="添加", command=save_word, style="Accent.TButton").pack(side=tk.RIGHT, padx=5)
        ttk.Button(btn_frame, text="取消", command=add_window.destroy).pack(side=tk.RIGHT, padx=5)
    
    def delete_word_dialog(self):
        """删除单词对话框"""
        # 获取选中的集合
        selected = self.sections_listbox.curselection()
        if not selected:
            messagebox.showwarning("未选择", "请先选择一个集合!")
            return
        
        section = self.sections_listbox.get(selected[0]).split()[1]
        
        if not self.vocab[section]:
            messagebox.showinfo("集合为空", f"集合 '{section}' 中没有单词!")
            return
        
        # 创建删除单词窗口
        delete_window = tk.Toplevel(self.root)
        delete_window.title(f"删除单词 - 集合 {section}")
        delete_window.geometry("500x400")
        delete_window.transient(self.root)
        delete_window.grab_set()
        
        # 单词列表
        list_frame = ttk.Frame(delete_window)
        list_frame.pack(fill=tk.BOTH, expand=True, padx=10, pady=10)
        
        scrollbar = ttk.Scrollbar(list_frame)
        scrollbar.pack(side=tk.RIGHT, fill=tk.Y)
        
        word_listbox = tk.Listbox(list_frame, selectmode=tk.MULTIPLE, font=("Arial", 11), 
                                 yscrollcommand=scrollbar.set, width=50, height=15)
        word_listbox.pack(fill=tk.BOTH, expand=True)
        scrollbar.config(command=word_listbox.yview)
        
        # 填充单词列表
        for chinese, english in self.vocab[section].items():
            # 显示错误次数（如果存在）
            mistake_count = self.get_mistake_count(chinese, section)
            display_text = f"{chinese} = {english}"
            if mistake_count > 0:
                display_text += f" (错误: {mistake_count}次)"
            word_listbox.insert(tk.END, display_text)
        
        # 按钮框架
        btn_frame = ttk.Frame(delete_window)
        btn_frame.pack(fill=tk.X, pady=10, padx=20)
        
        def delete_selected():
            selected = word_listbox.curselection()
            if not selected:
                messagebox.showwarning("未选择", "请选择要删除的单词!")
                return
            
            if messagebox.askyesno("确认删除", f"确定要删除选中的 {len(selected)} 个单词吗?"):
                # 倒序删除避免索引问题
                for index in selected[::-1]:
                    chinese = word_listbox.get(index).split('=')[0].strip()
                    del self.vocab[section][chinese]
                    
                    # 同时删除错误计数
                    if chinese in self.mistake_counts and section in self.mistake_counts[chinese]:
                        del self.mistake_counts[chinese][section]
                        # 如果没有其他错误计数，删除整个条目
                        if not self.mistake_counts[chinese]:
                            del self.mistake_counts[chinese]
                    
                    word_listbox.delete(index)
                
                self.save_vocabulary()
                self.save_mistake_counts()
                self.update_sections_list()
                messagebox.showinfo("删除成功", f"已删除 {len(selected)} 个单词!")
        
        ttk.Button(btn_frame, text="删除选中", command=delete_selected, style="Accent.TButton").pack(side=tk.RIGHT, padx=5)
        ttk.Button(btn_frame, text="关闭", command=delete_window.destroy).pack(side=tk.RIGHT, padx=5)
    
    def get_mistake_count(self, chinese, section):
        """获取指定单词的错误次数"""
        if chinese in self.mistake_counts and section in self.mistake_counts[chinese]:
            return self.mistake_counts[chinese][section]
        return 0
    
    def increment_mistake_count(self, chinese, section):
        """增加指定单词的错误计数"""
        if chinese not in self.mistake_counts:
            self.mistake_counts[chinese] = {}
        if section not in self.mistake_counts[chinese]:
            self.mistake_counts[chinese][section] = 0
        
        self.mistake_counts[chinese][section] += 1
        self.save_mistake_counts()
    
    def reset_mistake_counts(self):
        """重置所有错误计数"""
        if not self.mistake_counts:
            messagebox.showinfo("提示", "当前没有错误计数记录")
            return
        
        if messagebox.askyesno("确认重置", "确定要重置所有单词的错误计数吗？\n此操作不可撤销!"):
            self.mistake_counts = {}
            self.save_mistake_counts()
            messagebox.showinfo("成功", "所有错误计数已重置!")
    
    def show_mistake_counts(self):
        """显示错误次数最多的单词"""
        if not self.mistake_counts:
            messagebox.showinfo("提示", "当前没有错误计数记录")
            return
        
        # 创建窗口
        mistake_window = tk.Toplevel(self.root)
        mistake_window.title("单词错误次数统计")
        mistake_window.geometry("600x500")
        mistake_window.transient(self.root)
        mistake_window.grab_set()
        
        # 标题
        ttk.Label(mistake_window, text="单词错误次数统计", font=("Arial", 14, "bold")).pack(pady=10)
        
        # 创建框架
        frame = ttk.Frame(mistake_window)
        frame.pack(fill=tk.BOTH, expand=True, padx=10, pady=5)
        
        # 表头
        header_frame = ttk.Frame(frame)
        header_frame.pack(fill=tk.X)
        
        ttk.Label(header_frame, text="单词", width=20, style="MistakeHeader.TLabel").pack(side=tk.LEFT, padx=1, pady=1)
        ttk.Label(header_frame, text="英文", width=20, style="MistakeHeader.TLabel").pack(side=tk.LEFT, padx=1, pady=1)
        ttk.Label(header_frame, text="所属集合", width=10, style="MistakeHeader.TLabel").pack(side=tk.LEFT, padx=1, pady=1)
        ttk.Label(header_frame, text="错误次数", width=10, style="MistakeHeader.TLabel").pack(side=tk.LEFT, padx=1, pady=1)
        
        # 创建滚动区域
        canvas = tk.Canvas(frame)
        scrollbar = ttk.Scrollbar(frame, orient=tk.VERTICAL, command=canvas.yview)
        scrollable_frame = ttk.Frame(canvas)
        
        scrollable_frame.bind(
            "<Configure>",
            lambda e: canvas.configure(scrollregion=canvas.bbox("all")))
        
        canvas.create_window((0, 0), window=scrollable_frame, anchor="nw")
        canvas.configure(yscrollcommand=scrollbar.set)
        
        canvas.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        scrollbar.pack(side=tk.RIGHT, fill=tk.Y)
        
        # 收集所有错误记录
        all_mistakes = []
        for chinese, sections in self.mistake_counts.items():
            for section, count in sections.items():
                # 查找英文翻译
                english = ""
                if section in self.vocab and chinese in self.vocab[section]:
                    english = self.vocab[section][chinese]
                all_mistakes.append((chinese, english, section, count))
        
        # 按错误次数排序
        all_mistakes.sort(key=lambda x: x[3], reverse=True)
        
        # 显示错误记录
        for idx, (chinese, english, section, count) in enumerate(all_mistakes):
            row_frame = ttk.Frame(scrollable_frame)
            row_frame.pack(fill=tk.X)
            
            # 交替行背景色
            bg_color = "#FFFFFF" if idx % 2 == 0 else "#F0F8FF"
            
            ttk.Label(row_frame, text=chinese, width=20, background=bg_color).pack(side=tk.LEFT, padx=1, pady=1)
            ttk.Label(row_frame, text=english, width=20, background=bg_color).pack(side=tk.LEFT, padx=1, pady=1)
            ttk.Label(row_frame, text=section, width=10, background=bg_color).pack(side=tk.LEFT, padx=1, pady=1)
            
            # 错误次数使用不同颜色
            fg_color = "red" if count >= 3 else "orange" if count >= 2 else "black"
            mistake_label = ttk.Label(row_frame, text=str(count), width=10, 
                                    foreground=fg_color, font=("Arial", 10, "bold"), 
                                    background=bg_color)
            mistake_label.pack(side=tk.LEFT, padx=1, pady=1)

    def create_rating_display(self):
        """创建评级显示区域"""
        rating_frame = ttk.Frame(self.root)
        rating_frame.pack(fill=tk.X, padx=20, pady=5)
        
        # 当前评级标签
        self.rating_label = ttk.Label(rating_frame, text="当前评级: Unrated (0)", 
                                     font=("Arial", 12, "bold"))
        self.rating_label.pack(side=tk.LEFT)
        
        # 查看历史按钮
        ttk.Button(rating_frame, text="评级历史", command=self.show_rating_history, 
                  style="Section.TButton").pack(side=tk.RIGHT, padx=5)
        
        # 初始化评级显示
        self.update_rating_display()
    
    def load_rating_history(self):
        """加载评级历史"""
        try:
            with open(RATING_FILE, 'r', encoding='utf-8') as f:
                return json.load(f)
        except (FileNotFoundError, json.JSONDecodeError):
            return []
    
    def load_user_data(self):
        """加载用户数据"""
        try:
            with open(USER_DATA_FILE, 'r', encoding='utf-8') as f:
                data = json.load(f)
                # 确保数据格式正确
                if "current_rating" not in data:
                    data["current_rating"] = 0
                if "k_factor" not in data:
                    data["k_factor"] = 64  # 初始K因子
                if "test_count" not in data:
                    data["test_count"] = 0
                return data
        except (FileNotFoundError, json.JSONDecodeError):
            return {"current_rating": 0, "k_factor": 64, "test_count": 0}
    
    def save_rating_history(self):
        """保存评级历史"""
        with open(RATING_FILE, 'w', encoding='utf-8') as f:
            json.dump(self.rating_history, f, ensure_ascii=False, indent=2)
    
    def save_user_data(self):
        """保存用户数据"""
        with open(USER_DATA_FILE, 'w', encoding='utf-8') as f:
            json.dump(self.user_data, f, ensure_ascii=False, indent=2)
    
    def update_rating_display(self):
        """更新评级显示"""
        rating = self.user_data["current_rating"]
        color = self.get_rating_color(rating)
        title = self.get_rating_title(rating)
        
        self.rating_label.config(
            text=f"当前评级: {title} ({rating})", 
            foreground=color,
            font=("Arial", 12, "bold")
        )
    
    def get_rating_color(self, rating):
        """根据评级获取颜色"""
        if rating < 1200:
            return "#808080"  # 灰色
        elif rating < 1400:
            return "#008000"  # 绿色
        elif rating < 1600:
            return "#03899e"  # 青色
        elif rating < 1900:
            return "#0000FF"  # 蓝色
        elif rating < 2100:
            return "#aa00aa"  # 紫色
        elif rating < 2300:
            return "#FF8C00"  # 橙色
        elif rating < 2400:
            return "#FF8C00"  # 橙色
        elif rating < 2600:
            return "#FF0000"  # 红色
        elif rating < 3000:
            return "#FF0000"  # 红色
        elif rating < 4000:
            return "#000000"  # 黑色（首字母）
        else:
            return "#FF0000"  # 红色（首字母）
    
    def get_rating_title(self, rating):
        """根据评级获取称号"""
        if rating < 1200:
            return "Newbie"
        elif rating < 1400:
            return "Pupil"
        elif rating < 1600:
            return "Specialist"
        elif rating < 1900:
            return "Expert"
        elif rating < 2100:
            return "Candidate Master"
        elif rating < 2300:
            return "Master"
        elif rating < 2400:
            return "International Master"
        elif rating < 2600:
            return "Grandmaster"
        elif rating < 3000:
            return "International Grandmaster"
        elif rating < 4000:
            return "Legendary Grandmaster"
        else:
            return "Tourist"
    
    def show_rating_history(self):
        """显示评级历史"""
        if not self.rating_history:
            messagebox.showinfo("评级历史", "暂无评级历史记录")
            return
        
        # 创建窗口
        history_window = tk.Toplevel(self.root)
        history_window.title("评级历史")
        history_window.geometry("800x500")
        history_window.transient(self.root)
        history_window.grab_set()
        
        # 标题
        ttk.Label(history_window, text="评级历史记录", font=("Arial", 14, "bold")).pack(pady=10)
        
        # 创建框架
        frame = ttk.Frame(history_window)
        frame.pack(fill=tk.BOTH, expand=True, padx=10, pady=5)
        
        # 表头
        header_frame = ttk.Frame(frame)
        header_frame.pack(fill=tk.X)
        
        columns = ["序号", "时间", "单词集合", "单词数量", "正确率", "表现分", "评级前", "评级后"]
        widths = [5, 20, 15, 10, 10, 10, 10, 10]
        
        for i, (col, width) in enumerate(zip(columns, widths)):
            ttk.Label(header_frame, text=col, width=width, style="MistakeHeader.TLabel").grid(row=0, column=i, padx=1, pady=1)
        
        # 创建滚动区域
        canvas = tk.Canvas(frame)
        scrollbar = ttk.Scrollbar(frame, orient=tk.VERTICAL, command=canvas.yview)
        scrollable_frame = ttk.Frame(canvas)
        
        scrollable_frame.bind(
            "<Configure>",
            lambda e: canvas.configure(scrollregion=canvas.bbox("all")))
        
        canvas.create_window((0, 0), window=scrollable_frame, anchor="nw")
        canvas.configure(yscrollcommand=scrollbar.set)
        
        canvas.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        scrollbar.pack(side=tk.RIGHT, fill=tk.Y)
        
        # 显示历史记录
        for idx, record in enumerate(self.rating_history):
            row_frame = ttk.Frame(scrollable_frame)
            row_frame.pack(fill=tk.X)
            
            # 交替行背景色
            bg_color = "#FFFFFF" if idx % 2 == 0 else "#F0F8FF"
            
            # 序号
            ttk.Label(row_frame, text=str(idx+1), width=5, background=bg_color).grid(row=0, column=0, padx=1, pady=1)
            # 时间
            ttk.Label(row_frame, text=record["time"], width=20, background=bg_color).grid(row=0, column=1, padx=1, pady=1)
            # 单词集合
            sections = ", ".join(record["sections"])
            ttk.Label(row_frame, text=sections, width=15, background=bg_color).grid(row=0, column=2, padx=1, pady=1)
            # 单词数量
            ttk.Label(row_frame, text=str(record["total_words"]), width=10, background=bg_color).grid(row=0, column=3, padx=1, pady=1)
            # 正确率
            accuracy = f"{record['accuracy']:.1f}%"
            ttk.Label(row_frame, text=accuracy, width=10, background=bg_color).grid(row=0, column=4, padx=1, pady=1)
            # 表现分 - 使用评级颜色
            performance = record["performance"]
            perf_color = self.get_rating_color(performance)
            perf_label = ttk.Label(row_frame, text=str(int(performance)), width=10, background=bg_color)
            perf_label.config(foreground=perf_color, font=("Arial", 10, "bold"))
            perf_label.grid(row=0, column=5, padx=1, pady=1)
            # 评级前
            rating_before = record["rating_before"]
            before_color = self.get_rating_color(rating_before)
            before_label = ttk.Label(row_frame, text=str(rating_before), width=10, background=bg_color)
            before_label.config(foreground=before_color, font=("Arial", 10, "bold"))
            before_label.grid(row=0, column=6, padx=1, pady=1)
            # 评级后
            rating_after = record["rating_after"]
            after_color = self.get_rating_color(rating_after)
            after_label = ttk.Label(row_frame, text=str(rating_after), width=10, background=bg_color)
            after_label.config(foreground=after_color, font=("Arial", 10, "bold"))
            after_label.grid(row=0, column=7, padx=1, pady=1)

    def start_test(self):
        """开始听写测试"""
        selected = self.sections_listbox.curselection()
        if not selected:
            messagebox.showwarning("未选择", "请选择至少一个集合!")
            return
        
        # 获取选中的集合
        self.current_sections = []
        total_words = 0
        for index in selected:
            section = self.sections_listbox.get(index).split()[1]
            self.current_sections.append(section)
            if section in self.vocab:
                total_words += len(self.vocab[section])
        
        # 检查单词数量是否足够评级测试
        self.rated_test = False
        if total_words >= 100:
            response = messagebox.askquestion("评级测试", 
                f"本次测试包含 {total_words} 个单词，是否计入评级?\n\n"
                "选择'是'将影响您的等级分，选择'否'将不计入评级。",
                icon='question')
            self.rated_test = (response == 'yes')
        else:
            self.rated_test = False
        
        # 合并单词
        self.current_words = []
        for section in self.current_sections:
            if section in self.vocab:
                for chinese, english in self.vocab[section].items():
                    self.current_words.append((chinese, english, section))
        
        if not self.current_words:
            messagebox.showwarning("无单词", "选中的集合中没有单词!")
            return
        
        # 记录每个单词的尝试次数（用于评级计算）
        self.word_attempts = {}
        for chinese, _, section in self.current_words:
            self.word_attempts[chinese] = {
                "attempts": 0,
                "correct": False,
                "section": section
            }
        
        # 打乱单词顺序
        random.shuffle(self.current_words)
        self.current_index = 0
        self.total_words = len(self.current_words)
        self.correct_count = 0
        self.wrong_count = 0
        self.wrong_words = []
        self.current_attempts = 0
        self.current_word_correct = False
        self.current_hint_level = 0
        
        # 更新测试信息 - 显示当前评级（带颜色）
        section_names = ", ".join(self.current_sections)
        test_type = "评级测试" if self.rated_test else "普通测试"
        
        # 获取当前评级信息
        current_rating = self.user_data["current_rating"]
        rating_title = self.get_rating_title(current_rating)
        rating_color = self.get_rating_color(current_rating)
        
        # 创建带颜色的评级信息文本
        rating_text = f"{rating_title} ({current_rating})"
        
        # 更新测试信息标签
        self.test_info.config(
            text=f"{test_type}: {section_names} | 单词总数: {self.total_words} | 当前评级: {rating_text}",
            foreground=rating_color,
            font=("Arial", 12)
        )
        
        # 清空结果区域
        for widget in self.result_frame.winfo_children():
            widget.destroy()
        
        # 确保输入框可用
        self.answer_entry.config(state=tk.NORMAL)
        
        # 确保测试按钮可见
        self.check_btn.pack(side=tk.LEFT, padx=5)
        # self.skip_btn.pack(side=tk.LEFT, padx=5)
        self.end_btn.pack(side=tk.RIGHT, padx=5)
        
        # 隐藏重新测试按钮
        self.retry_btn.pack_forget()
        
        # 显示第一个单词
        self.test_in_progress = True
        self.show_question()
    
    def retry_test(self):
        """重新测试相同的单词集合"""
        if not self.current_sections:
            messagebox.showinfo("提示", "没有之前的测试记录")
            return
        
        # 重新开始测试
        self.start_test()
    
    def show_question(self):
        """显示当前问题"""
        if self.current_index < self.total_words:
            chinese, _, _ = self.current_words[self.current_index]
            self.question_label.config(text=f"{chinese} 的英文是？")
            self.answer_entry.delete(0, tk.END)
            self.feedback_label.config(text="")
            self.current_attempts = 0
            self.current_word_correct = False
            self.current_hint_level = 0
            self.update_attempts_label()
            self.update_progress_label()
            self.update_hint_label()  # 重置提示
            self.answer_entry.focus()
        else:
            self.end_test()
    
    def update_attempts_label(self):
        """更新尝试次数显示"""
        if self.current_attempts > 0:
            attempts_left = 3 - self.current_attempts
            self.attempts_label.config(text=f"剩余尝试次数: {attempts_left}")
        else:
            self.attempts_label.config(text="")
    
    def update_progress_label(self):
        """更新进度标签"""
        progress = f"单词 {self.current_index + 1}/{self.total_words}"
        self.progress_label.config(text=progress)
    
    def update_hint_label(self):
        """更新提示标签"""
        if self.current_hint_level == 0:
            self.hint_label.config(text="")
        elif self.current_hint_level == 1:
            # 显示单词长度提示
            _, correct_english, _ = self.current_words[self.current_index]
            length = len(correct_english)
            self.hint_label.config(text=f"提示: 单词长度是 {length} 个字母")
        elif self.current_hint_level == 2:
            # 显示首字母提示
            _, correct_english, _ = self.current_words[self.current_index]
            first_letter = correct_english[0].upper()
            self.hint_label.config(text=f"提示: 首字母是 {first_letter}")
    
    def check_answer(self, event=None):
        """检查答案"""
        if not self.test_in_progress or self.current_index >= self.total_words:
            return
        
        user_answer = self.answer_entry.get().strip()
        if not user_answer:
            messagebox.showwarning("未输入", "请输入英文单词!")
            return
        
        chinese, correct_english, section = self.current_words[self.current_index]
        
        # 记录尝试次数（用于评级计算）
        if chinese not in self.word_attempts:
            self.word_attempts[chinese] = {
                "attempts": 0,
                "correct": False,
                "section": section
            }
        
        self.word_attempts[chinese]["attempts"] += 1
        self.current_attempts += 1
        
        if user_answer.lower() == correct_english.lower():
            # 答对处理
            self.feedback_label.config(text="✅ Accepted!", foreground="green")
            self.correct_count += 1
            self.current_word_correct = True
            self.word_attempts[chinese]["correct"] = True
            
            self.root.after(250, self.next_question)
        else:
            # 答错处理
            if self.current_attempts < 3:
                # 还有尝试机会
                self.feedback_label.config(text="❌ Try again! 请再试一次", foreground="orange")
                
                # 根据尝试次数显示提示
                if self.current_attempts == 1:
                    self.current_hint_level = 1  # 第一次错误，显示单词长度
                elif self.current_attempts == 2:
                    self.current_hint_level = 2  # 第二次错误，显示首字母
                
                self.update_hint_label()
                self.update_attempts_label()
                self.answer_entry.delete(0, tk.END)
                self.answer_entry.focus()
            else:
                # 三次尝试都错误
                self.feedback_label.config(text=f"❌ Wrong Answer! 正确答案: {correct_english}", foreground="red")
                self.wrong_count += 1
                self.wrong_words.append((chinese, correct_english, section))
                
                # 增加错误计数
                self.increment_mistake_count(chinese, section)
                self.root.after(1500, self.next_question)
    
    def next_question(self):
        """显示下一个问题"""
        # 只有在当前单词未答对且尝试次数用尽时才移动到下一个单词
        if self.current_word_correct or self.current_attempts >= 3:
            self.current_index += 1
            self.show_question()
        else:
            # 当前单词还有尝试机会，不需要移动到下一个单词
            self.answer_entry.delete(0, tk.END)
            self.answer_entry.focus()
    
    def end_test(self):
        """结束测试并显示结果"""
        self.test_in_progress = False

        # 如果是评级测试，计算新的评级
        if self.rated_test:
            old_rating, new_rating, performance = self.calculate_new_rating()
        
        # 更新问题区域
        self.question_label.config(text="测试结束!")
        self.answer_entry.delete(0, tk.END)
        self.answer_entry.config(state=tk.NORMAL)  # 保持输入框可用
        self.feedback_label.config(text="")
        self.attempts_label.config(text="")
        self.progress_label.config(text="")
        self.hint_label.config(text="")
        
        # 隐藏测试按钮，显示重新测试按钮
        self.check_btn.pack_forget()
        self.skip_btn.pack_forget()
        self.end_btn.pack_forget()
        self.retry_btn.pack(pady=10)
        
        # 显示结果
        for widget in self.result_frame.winfo_children():
            widget.destroy()
        
        total = self.correct_count + self.wrong_count
        
        # 结果标签
        result_text = f"测试结果: 共 {total} 个单词"
        ttk.Label(self.result_frame, text=result_text, font=("Arial", 12, "bold")).pack(pady=5)
        
        # 正确率
        if total > 0:
            accuracy = self.correct_count / total * 100
            accuracy_text = f"正确率: {accuracy:.1f}%"
            ttk.Label(self.result_frame, text=accuracy_text, font=("Arial", 14, "bold"), 
                     foreground="green" if accuracy >= 80 else "orange" if accuracy >= 60 else "red").pack(pady=5)
        
        # 如果是评级测试，显示表现分和评级变化
        if self.rated_test:
            # 表现分（带颜色）
            perf_color = self.get_rating_color(performance)
            perf_label = ttk.Label(self.result_frame, 
                                  text=f"表现分: {int(performance)}", 
                                  font=("Arial", 12, "bold"),
                                  foreground=perf_color)
            perf_label.pack(pady=5)
            
            # 评级变化（带颜色）
            rating_frame = ttk.Frame(self.result_frame)
            rating_frame.pack(pady=5)
            
            ttk.Label(rating_frame, text="评级变化: ", font=("Arial", 12)).pack(side=tk.LEFT)
            
            # 旧评级（带颜色）
            old_color = self.get_rating_color(old_rating)
            ttk.Label(rating_frame, text=f"{int(old_rating)}", 
                     font=("Arial", 12, "bold"), foreground=old_color).pack(side=tk.LEFT)
            
            ttk.Label(rating_frame, text=" → ", font=("Arial", 12)).pack(side=tk.LEFT)
            
            # 新评级（带颜色）
            new_color = self.get_rating_color(new_rating)
            ttk.Label(rating_frame, text=f"{int(new_rating)}", 
                     font=("Arial", 12, "bold"), foreground=new_color).pack(side=tk.LEFT)
            
            # 评级变化量
            change = new_rating - old_rating
            change_color = "green" if change >= 0 else "red"
            ttk.Label(rating_frame, text=f" ({'+' if change >= 0 else ''}{change:.1f})", 
                     font=("Arial", 12), foreground=change_color).pack(side=tk.LEFT)
        
        # 详情框架
        detail_frame = ttk.Frame(self.result_frame)
        detail_frame.pack(fill=tk.BOTH, pady=10)
        
        # 正确单词
        correct_frame = ttk.LabelFrame(detail_frame, text=f"正确 ({self.correct_count})")
        correct_frame.pack(side=tk.LEFT, fill=tk.BOTH, expand=True, padx=5)
        
        correct_list = scrolledtext.ScrolledText(correct_frame, height=8, font=("Arial", 10))
        correct_list.pack(fill=tk.BOTH, expand=True)
        correct_list.config(state=tk.NORMAL)
        
        # 错误单词（按错误次数排序）
        wrong_frame = ttk.LabelFrame(detail_frame, text=f"错误 ({self.wrong_count})")
        wrong_frame.pack(side=tk.RIGHT, fill=tk.BOTH, expand=True, padx=5)
        
        wrong_list = scrolledtext.ScrolledText(wrong_frame, height=8, font=("Arial", 10))
        wrong_list.pack(fill=tk.BOTH, expand=True)
        wrong_list.config(state=tk.NORMAL)
        
        # 填充正确单词列表
        if total > 0:
            for i in range(min(self.correct_count, len(self.current_words))):
                chinese, english, _ = self.current_words[i]
                correct_list.insert(tk.END, f"• {chinese} = {english}\n")
        
        # 填充错误单词列表（按错误次数排序）
        if self.wrong_words:
            # 为每个错误单词获取错误次数
            wrong_with_counts = []
            for chinese, english, section in self.wrong_words:
                count = self.get_mistake_count(chinese, section)
                wrong_with_counts.append((chinese, english, section, count))
            
            # 按错误次数从大到小排序
            wrong_with_counts.sort(key=lambda x: x[3], reverse=True)
            
            for chinese, english, section, count in wrong_with_counts:
                wrong_list.insert(tk.END, f"• {chinese} = {english} (错误次数: {count})\n")
        
        correct_list.config(state=tk.DISABLED)
        wrong_list.config(state=tk.DISABLED)
    
    def calculate_new_rating(self):
        """计算新的评级"""
        # 1. 保存旧评级
        old_rating = self.user_data["current_rating"]
        
        # 2. 计算基本表现分
        accuracy = self.correct_count / self.total_words * 100
        
        # 3. 计算罚时影响（尝试次数越多，罚时越高）
        total_penalty = 0
        max_penalty_per_word = 30  # 每个单词最大罚时（相当于3次尝试）
        
        for word_data in self.word_attempts.values():
            attempts = word_data["attempts"]
            # 答对：罚时 = (尝试次数 - 1) * 10
            # 答错：罚时 = 最大罚时
            if word_data["correct"]:
                penalty = min((attempts - 1) * 10, max_penalty_per_word)
            else:
                penalty = max_penalty_per_word
            total_penalty += penalty
        
        # 平均罚时（秒）
        avg_penalty = total_penalty / self.total_words
        
        # 4. 计算表现分（正确率越高、平均罚时越低，表现分越高）
        # 基础分1000，正确率每1%加10分，罚时每1秒减1分
        performance = 1000 + accuracy * 10 - avg_penalty
        
        # 5. 应用非线性调整（正确率越高，奖励越大）
        if accuracy >= 95:
            performance *= 1.2  # 95%以上额外奖励20%
        elif accuracy >= 90:
            performance *= 1.15
        elif accuracy >= 85:
            performance *= 1.1
        elif accuracy >= 80:
            performance *= 1.05
        
        # 6. 根据测试规模调整（单词越多，影响越大）
        scale_factor = min(1.0, self.total_words / 200)  # 200单词为基准
        performance *= 1.0 + scale_factor * 0.3  # 最多增加30%
        
        # 7. 计算新评级（Elo-like 系统）
        test_count = self.user_data["test_count"]
        
        # K因子：测试次数越多，变化越小
        k_factor = self.user_data["k_factor"]
        if test_count < 10:
            k_factor = 64  # 新用户变化大
        elif test_count < 30:
            k_factor = 48
        elif test_count < 50:
            k_factor = 32
        else:
            k_factor = 24
        
        # 期望表现分（当前评级对应的表现分）
        expected_performance = old_rating
        
        # 计算评级变化
        rating_change = k_factor * (performance - expected_performance) / 1000
        new_rating = old_rating + rating_change
        
        # 确保评级不会为负
        if new_rating < 0:
            new_rating = 0
        
        # 更新用户数据
        self.user_data["current_rating"] = new_rating
        self.user_data["test_count"] += 1
        self.user_data["k_factor"] = max(16, k_factor * 0.95)  # 每次测试后K因子衰减
        
        # 保存评级历史记录
        history_record = {
            "time": datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
            "index": len(self.rating_history) + 1,
            "sections": self.current_sections,
            "total_words": self.total_words,
            "accuracy": accuracy,
            "performance": performance,
            "rating_before": old_rating,
            "rating_after": new_rating
        }
        
        self.rating_history.append(history_record)
        
        # 保存数据
        self.save_rating_history()
        self.save_user_data()
        
        # 更新显示
        self.update_rating_display()
        
        # 显示评级变化
        messagebox.showinfo("评级更新", 
            f"测试结果已计入评级！\n\n"
            f"正确率: {accuracy:.1f}%\n"
            f"表现分: {performance:.1f}\n"
            f"评级变化: {old_rating} → {new_rating} ({'+' if rating_change >= 0 else ''}{rating_change:.1f})\n"
            f"新称号: {self.get_rating_title(new_rating)}")
            
        return old_rating, new_rating, performance

if __name__ == "__main__":
    root = tk.Tk()
    app = VocabularyApp(root)
    root.mainloop()