# 配置中科大源
sudo sed -i 's/archive.ubuntu.com/mirrors.ustc.edu.cn/g' /etc/apt/sources.list
sudo apt-get update

# 安装必备软件
sudo apt-get install openssh-server g++ gdb gdbserver vim

# 配置openssl
1. 重新安装openssl
sudo apt-get remove openssh-server 
sudo apt-get install openssh-server
原因是：默认安装的ssl配置不准确，卸载后再安装会自动配置

2. 编辑 sshd_config 配置文件
sudo vim /etc/ssh/sshd_config
修改 PasswordAuthentication yes

3. 每次打开bash后运行sshd
`sudo /etc/init.d/ssh start` 或者 `service ssh start`


