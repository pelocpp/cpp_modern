// =====================================================================================
// FileSystem
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <filesystem>

namespace FileSystemDemo {

    void test_01(std::string path) {
        // examine path object
        std::cout << "Examine " << path << ':' << '\n';
        std::filesystem::path current;

        if (path.empty()) {
            current = std::filesystem::current_path();
        }
        else {
            current = { path };
        }

        if (std::filesystem::exists(current)) {
            std::cout
                << "exists() = " << std::filesystem::exists(current) << '\n'
                << "root_name() = " << current.root_name() << '\n'
                << "root_path() = " << current.root_path() << '\n'
                << "relative_path() = " << current.relative_path() << '\n'
                << "parent_path() = " << current.parent_path() << '\n'
                << "filename() = " << current.filename() << '\n'
                << "stem() = " << current.stem() << '\n'
                << "extension() = " << current.extension() << '\n';
        }
        std::cout << std::endl;
    }

    void test_02() {
        // iterating over path object

        // note: use of raw character string notation
        std::filesystem::path p(R"(C:\Development\GitRepositoryCPlusPlus\Readme_Ssh.txt)");

        // range-based loop
        int i = 0;
        for (const auto& part : p)
            std::cout << "part: " << i++ << " = " << part << '\n';
        std::cout << std::endl;

        // or iterator based loop
        i = 0;
        std::filesystem::path::iterator begin = p.begin();
        std::filesystem::path::iterator end = p.end();
        while (begin != end) {
            std::cout << "part: " << i++ << " = " << *begin << '\n';
            begin++;
        }
        std::cout << std::endl;
    }

    std::uintmax_t computeFileSize(const std::filesystem::path& file) {

        std::filesystem::path p{ file };
        if (std::filesystem::exists(p) && std::filesystem::is_regular_file(p)) {
            std::error_code err = std::error_code{};
            auto filesize = std::filesystem::file_size(p, err);
            if (filesize != static_cast<uintmax_t>(-1)) {
                return filesize;
            }
        }

        return static_cast<uintmax_t>(-1);
    }

    void test_03(std::string path) {
        std::uintmax_t size = computeFileSize(path);
        std::cout << "Size of File: " << size << '\n';
    }

    // reading contents of directory
    void readDirectory01(const std::string& name)
    {
        std::filesystem::path p(name);
        std::filesystem::directory_iterator start(p);
        std::filesystem::directory_iterator end;

        std::for_each(start, end, [i = 0](const std::filesystem::directory_entry& entry) mutable {
            std::string s{ entry.path().filename().string() };
            std::cout << "Entry: " << i++ << " = " << s << '\n';
            }
        );
    }

    void readDirectory02(const std::string& name, std::vector<std::string>& vec)
    {
        std::filesystem::path p(name);
        std::filesystem::directory_iterator start(p);
        std::filesystem::directory_iterator end;

        std::transform(
            start,
            end,
            std::back_inserter(vec),
            [](const std::filesystem::directory_entry& entry) {
                std::string s{ entry.path().filename().string() };
                return s;
            }
        );
    }

    void test_04a(std::string path) {
        readDirectory01(path);
    }

    void test_04b(std::string path) {

        std::vector<std::string> dir;
        readDirectory02(path, dir);

        int i = 0;
        for (const std::string& entry : dir) {
            std::cout << "Entry: " << i++ << " = " << entry << '\n';
        }

        // or

        std::copy(
            dir.begin(),
            dir.end(),
            std::ostream_iterator<std::string>(std::cout, "\n")
        );
    }

    // traversing a directory recursively
    void displayFileInfo(const std::filesystem::directory_entry& entry, std::string& lead, const std::filesystem::path& filename)
    {
        std::cout << lead << filename << ", " << computeFileSize(entry) << "\n";
    }

    void displayDirectoryTreeImp(const std::filesystem::path& p, int level)
    {
        if (std::filesystem::exists(p) && std::filesystem::is_directory(p)) {
            std::string lead = (level ==0) ? std::string("") : std::string(level * 4, ' ');

            for (const auto& entry : std::filesystem::directory_iterator(p)) {
                const std::filesystem::path filename = entry.path().filename();
                if (std::filesystem::is_directory(entry.status())) {
                    std::cout << lead << "[+] " << filename << "\n";
                    displayDirectoryTreeImp(entry, level + 1);
                    std::cout << "\n";
                }
                else if (std::filesystem::is_regular_file(entry.status())) {
                    displayFileInfo(entry, lead, filename);
                }
                else {
                    std::cout << lead << "[?]" << filename << "\n";
                }
            }
        }
    }

    void displayDirectoryTree(const std::filesystem::path& p)
    {
        displayDirectoryTreeImp(p, 0);
    }

    void test_05(std::string path) {
        // traversing a directory recursively
        std::cout << "Examine " << path << ':' << '\n';
        std::filesystem::path current;

        if (path.empty()) {
            current = std::filesystem::current_path();
        }
        else {
            current = { path };
        }

        displayDirectoryTree(current);

        std::cout << std::endl;
    }
}

void main_filesystem()
{
    using namespace FileSystemDemo;

    test_01("");
    test_01("C:\\Development\\GitRepositoryCPlusPlus\\Readme_Ssh.txt");
    test_01("C:\\");
    test_01("C:\\Usersss");

    test_02();

    test_03("C:\\Development\\GitRepositoryCPlusPlus\\Readme_Ssh.txt");

    // note: use of raw character string notation
    constexpr const char* path =
        R"(C:\Development\GitRepositoryCPlusPlus\Cpp_DesignPatterns\CompositePattern)";

    test_04a(path);
    test_04b(path);

    test_05(path);
}

// =====================================================================================
// End-of-File
// =====================================================================================
