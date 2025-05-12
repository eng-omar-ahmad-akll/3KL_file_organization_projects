#include <iostream>
#include <filesystem>

using namespace std;
int main() {
    string your_folder_to_read_and_represent;
    cout << "Enter the folder path: ";
    cin >> your_folder_to_read_and_represent;
    int num_of_folders = 0, num_of_files = 0;
    try {
        if (filesystem::exists(your_folder_to_read_and_represent) && filesystem::is_directory(your_folder_to_read_and_represent)) {
            cout << "\nFiles and Folders in: " << your_folder_to_read_and_represent << "\n\n";

            for (const auto& entry : filesystem::recursive_directory_iterator(your_folder_to_read_and_represent)) {
                if (filesystem::is_directory(entry.path())) {
                    cout << " FOLDER " << entry.path().filename() << "\n";
                    num_of_folders++;
                }
                else {
                    cout << "FILE " << entry.path().filename() << "\n";
                    num_of_files++;
                }
            }
            cout << "\nSummary:\n";
            cout << "Total of your Folders: " << num_of_folders << "\n";
            cout << "Total of your Files: " << num_of_files << "\n";
        }
        else {
            cout << "Invalid path or not a directory!\n";
        }
    }
    catch (const filesystem::filesystem_error& e) {
        cout << "Error: " << e.what() << endl;
    }
    return 0;
}
