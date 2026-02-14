#!/usr/bin/env python3
"""
Change all #include "xxx.cpp" to #include "xxx.hpp" in cpp files under tests_split directory
"""

import os
import re
import glob

def fix_includes_in_file(filepath):
    """Fix include statements in a single file"""
    with open(filepath, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # Match #include "xxx.cpp" and replace with #include "xxx.hpp"
    # Pattern: #include "any_filename.cpp"
    pattern = r'#include\s+"([^"]+)\.cpp"'
    replacement = r'#include "\1.hpp"'
    
    new_content = re.sub(pattern, replacement, content)
    
    if new_content != content:
        with open(filepath, 'w', encoding='utf-8') as f:
            f.write(new_content)
        return True
    return False

def main():
    # tests_split directory path
    tests_split_dir = os.path.dirname(os.path.abspath(__file__))
    tests_split_dir = os.path.join(tests_split_dir, 'tests_split')
    
    # Get all cpp files
    cpp_files = glob.glob(os.path.join(tests_split_dir, '*.cpp'))
    
    modified_count = 0
    for filepath in cpp_files:
        if fix_includes_in_file(filepath):
            print(f"Modified: {os.path.basename(filepath)}")
            modified_count += 1
    
    print(f"\nTotal modified {modified_count} files")

if __name__ == '__main__':
    main()


