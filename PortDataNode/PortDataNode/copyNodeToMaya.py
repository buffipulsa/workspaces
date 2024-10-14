import os
import shutil
import argparse

def copy_file_if_exists(src_file, dest_dir):
    """
    Copy a file from src_file to dest_dir if both exist.

    :param src_file: Path to the source file
    :param dest_dir: Path to the destination directory
    """
    # Check if the source file exists
    if not os.path.isfile(src_file):
        print(f"Error: The source file '{src_file}' does not exist.")
        return

    # Check if the destination directory exists
    if not os.path.isdir(dest_dir):
        print(f"Error: The destination directory '{dest_dir}' does not exist.")
        return

    # Construct the destination file path
    dest_file = os.path.join(dest_dir, os.path.basename(src_file))

    # Copy the file
    try:
        shutil.copy2(src_file, dest_file)
        print(f"File '{src_file}' copied to '{dest_file}' successfully.")
    except Exception as e:
        print(f"Error copying file: {e}")

def main():
    # Set up argument parsing
    parser = argparse.ArgumentParser(description="Copy a file to a destination directory if both exist.")
    parser.add_argument("src_file", help="Path to the source file")
    parser.add_argument("dest_dir", help="Path to the destination directory")

    # Parse arguments
    args = parser.parse_args()

    # Call the copy function with the provided arguments
    copy_file_if_exists(args.src_file, args.dest_dir)

main()