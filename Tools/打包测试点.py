import os
import shutil
import zipfile
from pathlib import Path

def smart_process_test_cases(root_dir):
    """
    智能遍历：
    1. 寻找任何包含 'in' 和 'out' 子文件夹的目录
    2. 将 in/out 里的文件改名并拷贝到同级的 test 文件夹
    3. 打包 test 文件夹为 test.zip
    """
    root = Path(root_dir).expanduser().resolve()
    if not root.exists():
        print(f"❌ 路径不存在: {root}")
        return

    print(f"🚀 开始扫描: {root}")
    processed_count = 0

    # os.walk 递归遍历所有层级
    for dirpath, dirnames, filenames in os.walk(root):
        current_path = Path(dirpath)
        
        # 转换为小写列表以便查找，增强兼容性
        dirnames_lower = [d.lower() for d in dirnames]

        # 核心逻辑：如果当前目录下同时存在 in 和 out 文件夹
        if 'in' in dirnames_lower and 'out' in dirnames_lower:
            # 找到真实的文件夹名称（保持原有大小写）
            real_in_name = dirnames[dirnames_lower.index('in')]
            real_out_name = dirnames[dirnames_lower.index('out')]
            
            in_dir = current_path / real_in_name
            out_dir = current_path / real_out_name
            test_dir = current_path / 'test'
            zip_file = current_path / 'test.zip'

            print(f"📦 发现匹配目录: {current_path.relative_to(root)}")

            # 1. 创建或清空 test 文件夹
            if test_dir.exists():
                shutil.rmtree(test_dir)
            test_dir.mkdir(parents=True)

            # 2. 处理 in 文件夹 -> 拷贝并改名
            process_and_copy(in_dir, test_dir, '.in')

            # 3. 处理 out 文件夹 -> 拷贝并改名
            process_and_copy(out_dir, test_dir, '.out')

            # 4. 打包 test 文件夹
            create_zip(test_dir, zip_file)
            
            # 5. 可选：清理 test 文件夹（如果只想留 zip，可以取消下面注释）
            # shutil.rmtree(test_dir)
            
            processed_count += 1
            print(f"   ✅ 完成打包: {zip_file.name}")

    print(f"\n✨ 任务结束！共处理了 {processed_count} 组测试点。")

def process_and_copy(src_dir, dst_dir, target_suffix):
    """
    遍历源文件夹，修改后缀并拷贝到目标文件夹
    """
    for item in src_dir.iterdir():
        if item.is_file() and not item.name.startswith('.'):
            # 获取文件名（不含后缀）+ 新后缀
            new_name = item.stem + target_suffix
            target_path = dst_dir / new_name
            shutil.copy2(item, target_path)

def create_zip(source_dir, output_zip):
    """
    将文件夹内容打包成 zip
    """
    with zipfile.ZipFile(output_zip, 'w', zipfile.ZIP_DEFLATED) as zipf:
        for file in source_dir.iterdir():
            if file.is_file():
                # 第一个参数是完整路径，第二个参数是 zip 里的相对路径
                zipf.write(file, arcname=file.name)

if __name__ == "__main__":
    # 配置你的根目录
    USER_DOWNLOADS = '/Users/s/Downloads'
    
    smart_process_test_cases(USER_DOWNLOADS)