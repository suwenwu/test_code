import os
from pathlib import Path

def smart_rename_test_data(root_dir, dry_run=False):
    """
    智能遍历目录并修改后缀
    :param root_dir: 根目录路径
    :param dry_run: 脱靶测试模式（只打印不修改），默认为 False
    """
    root = Path(root_dir).expanduser().resolve()
    
    if not root.exists():
        print(f"❌ 错误: 路径不存在 -> {root}")
        return

    print(f"🚀 开始扫描目录: {root}")
    print(f"模式: {'[演示模式 - 不会实际修改]' if dry_run else '[正式执行模式]'}")
    
    rename_count = 0

    # 使用 os.walk 递归遍历所有文件夹
    for dirpath, dirnames, filenames in os.walk(root):
        current_dir = Path(dirpath)
        folder_name_lower = current_dir.name.lower()

        # 判断当前文件夹是否为目标文件夹
        target_suffix = None
        if folder_name_lower == 'in':
            target_suffix = '.in'
        elif folder_name_lower == 'out':
            target_suffix = '.out'

        if target_suffix:
            for filename in filenames:
                # 排除系统隐藏文件（如 .DS_Store）
                if filename.startswith('.'):
                    continue

                file_path = current_dir / filename
                
                # 检查是否已经是正确的后缀，避免重复操作
                if file_path.suffix.lower() == target_suffix:
                    continue

                # 构建新文件名：保留原名（不含旧后缀）+ 新后缀
                new_filename = file_path.stem + target_suffix
                new_file_path = current_dir / new_filename

                try:
                    if not dry_run:
                        # 执行重命名，如果目标已存在会覆盖
                        file_path.rename(new_file_path)
                    
                    print(f"✅ [{'RENAMED' if not dry_run else 'WILL_RENAME'}] "
                          f"{file_path.relative_to(root)} -> {new_filename}")
                    rename_count += 1
                except Exception as e:
                    print(f"❌ 失败: {file_path} -> {str(e)}")

    print(f"\n✨ 处理完成！共修改了 {rename_count} 个文件。")

if __name__ == "__main__":
    # 配置区
    TARGET_PATH = '/Users/s/Downloads'
    
    # 建议第一次运行先设为 True，确认没问题后再改回 False
    DRY_RUN_MODE = False 
    
    smart_rename_test_data(TARGET_PATH, dry_run=DRY_RUN_MODE)