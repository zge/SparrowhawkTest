#include <sparrowhawk/normalizer.h>

#ifdef _WIN32
#include <direct.h>
#define getcwd _getcwd
#define PATH_MAX MAX_PATH
#else
#include <unistd.h>
#endif

using namespace std;

string cwd() {
    char buf[PATH_MAX];
    getcwd(buf, PATH_MAX);
    return string(buf);
}

int main(int argc, char* argv[]) {

    string af_dir = cwd();
    string lang = "grammars"; // specify language
    af_dir = af_dir.substr(0, af_dir.size() - 3) + lang + "/"; //remove 'bin' from the end and add language
    //cout << "af_dir: " << af_dir << endl;

    speech::sparrowhawk::Normalizer normalizer;

    normalizer.Setup("sparrowhawk_configuration.ascii_proto", af_dir);

    string in;
    string out;

    string input = argv[1];
    string output = argv[2];
    cout << "input file: " << input << ", output file: " << output << endl;

    string line;
    ifstream infile (input);
    ofstream outfile;
    outfile.open(output);
    if (infile.is_open())
    {
      while ( getline (infile, line))
      {
	in = line;
	out = "";
        normalizer.Normalize(in, &out);
        cout << "INPUT: " << in << " --> OUTPUT: " << out << endl;
        outfile << out << endl;
      }
    }
    outfile.close();

    return 0;
}
