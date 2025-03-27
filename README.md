# LIJINGYI100996023
Personalized Password Generator ——prgm. Method &amp; Abstraction Person Project
# 个性化密码管理器

一个基于C++的命令行密码管理工具，可将用户输入的单词转化为安全密码并加密存储。

## 功能特性

- 🔐 主密码保护所有存储的密码
- 🔄 将单词转化为复杂密码（如：`hello` → `h3ll0!`）
- 💾 加密存储多个密码条目
- 🔍 按服务名称检索密码
- 📁 自动保存到本地文件

## 编译安装

### 依赖项
- GCC 9+ 或 Clang 10+
- OpenSSL 1.1+
- Make

### 编译步骤
```bash
# 安装依赖 (Ubuntu)
sudo apt install g++ make libssl-dev

# 克隆项目
git clone https://github.com/yourrepo/password-manager.git
cd password-manager

# 编译
make clean && make
