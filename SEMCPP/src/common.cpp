#include "common.hpp"
using namespace std;


// function taken from internet that splits  a string by a character
void split_string(const string &str, const string &splitBy, vector<string>& tokens)
{
    tokens.clear();
    /* Store the original string in the array, so we can loop the rest
     * of the algorithm. */
    tokens.push_back(str);

    // Store the split index in a 'size_t' (unsigned integer) type.
    size_t splitAt;
    // Store the size of what we're splicing out.
    size_t splitLen = splitBy.size();
    // Create a string for temporarily storing the fragment we're processing.
    std::string frag;
    // Loop infinitely - break is internal.
    while(true)
    {
        /* Store the last string in the vector, which is the only logical
         * candidate for processing. */
        frag = tokens.back();
        /* The index where the split is. */
        splitAt = frag.find(splitBy);
        // If we didn't find a new split point...
        if(splitAt == string::npos)
        {
            // Break the loop and (implicitly) return.
            break;
        }
        /* Put everything from the left side of the split where the string
         * being processed used to be. */
        tokens.back() = frag.substr(0, splitAt);
        /* Push everything from the right side of the split to the next empty
         * index in the vector. */
        tokens.push_back(frag.substr(splitAt+splitLen, frag.size()-(splitAt+splitLen)));
    }
}



// REQUIRES: index is within str
string grab_string_at_index(const string &str, const size_t index, 
                            const string &split){
    if(index >= str.size()){
        cerr << "grab_string_at_index bad arguments!\n\tEXITING";
        exit(1);
    }
    std::vector<std::string> tokens;

    split_string(str, split, tokens);

    return tokens[index];
}

void split_string_white(const string &str, vector<string>& tokens){
    tokens.clear();
    stringstream strm(str);
    string s = "";
    while(strm){
        strm >> s;
        tokens.push_back(s);
    }
}

string grab_string_at_index_white(const string &str, const size_t index){
    if(index >= str.size()){
        cerr << "grab_string_at_index bad arguments!\n\tEXITING";
        exit(1);
    }

    std::vector<std::string> tokens;

    split_string_white(str, tokens);

    return tokens[index];
}


string revCompDNA(string dna){
    string ret = "";
    for(size_t i = 0; i < dna.length(); ++i){
        switch(dna[i]){
            case 'A':
                ret += 'T';
            break;

            case 'C':
                ret += 'G';
            break;

            case 'G':
                ret += 'C';
            break;

            case 'T':
                ret += 'A';
            break;

            case 'a':
                ret += 't';
            break;

            case 'c':
                ret += 'g';
            break;

            case 'g':
                ret += 'c';
            break;

            case 't':
                ret += 'a';
            break;

            default:
                cerr << "\t error with revCompDNA" << endl;
                exit(1);
            break;
        }
    }

    return ret;

}




// grabbed from internet
void GetFilesInDirectory(std::vector<string> &out, const string &directory)
{
#ifdef WINDOWS
    HANDLE dir;
    WIN32_FIND_DATA file_data;

    if ((dir = FindFirstFile((directory + "/*").c_str(), &file_data)) == INVALID_HANDLE_VALUE)
        return; /* No files found */

    do {
        const string file_name = file_data.cFileName;
        const string full_file_name = directory + "/" + file_name;
        const bool is_directory = (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

        if (file_name[0] == '.')
            continue;

        if (is_directory)
            continue;

        out.push_back(full_file_name);
    } while (FindNextFile(dir, &file_data));

    FindClose(dir);
#else
    DIR *dir;
    struct dirent *ent;
    struct stat st;

    dir = opendir(directory.c_str());
    while ((ent = readdir(dir)) != NULL) {
        const string file_name = ent->d_name;
        const string full_file_name = directory + "/" + file_name;

        if (file_name[0] == '.')
            continue;

        if (stat(full_file_name.c_str(), &st) == -1)
            continue;

        const bool is_directory = (st.st_mode & S_IFDIR) != 0;

        if (is_directory)
            continue;

        out.push_back(full_file_name);
    }
    closedir(dir);
#endif
} // GetFilesInDirectory

void grab_string_3_index(string s, string &out){
    auto ptr = s.c_str();
    for(size_t i = 0; i < 2; ++i){
        while(!isspace(*ptr)){
            ++ptr;
        }
        ++ptr;
    }
    auto ptr2 = ptr;
    while(!isspace(*ptr2)){
        ++ptr2;
    }
    ++ptr2;
    out = string(ptr, ptr2 - ptr - 1);
}

bool fileExists(const string &filename){
  struct stat buffer;
  return (stat (filename.c_str(), &buffer) == 0);
}

// getlength accesses first(?) element of kmerHash and returns the key length
int getLength(const Dataset &data){
    if(data.kmerHash.empty()){
        std::cerr << "data.kmerHash is empty!!!!\n\tEXITING" << std::endl;
        exit(1);
    }
    return static_cast<int>(data.kmerHash.begin()->first.size());
}
