#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>

#include "aggregate_helpers.h"

using namespace std;

/*
 * Sort match samples by their score
 * @param match_scores: match_ID: score
 * @return sorted matches: match_IDs sorted by score
 */
vector<pair<string, int>> sort_matches(
        vector<pair<string, int>> match_scores) {
    vector<pair<string, int>> sorted_matches;
    // copy map to vector
    for (auto match : match_scores){
        sorted_matches.push_back(match);
    }
    // sort vector
    sort(sorted_matches.begin(), sorted_matches.end(),
        [](const pair<string, int> &a, const pair<string, int> &b){
        return a.second > b.second;
    });
    return sorted_matches;
}

/*
 * read in a list of sample IDs from file
 * @param query_samples_list: file of samples
 * @return query_samples: list of samples 
 */
vector<string> get_query_samples_list(
        string query_samples_list) {
    vector<string> query_samples;
    string line;
    ifstream file(query_samples_list);
    while (getline(file, line)) {
        query_samples.push_back(line);
    }
    return query_samples;
}


/*
 * read in match file
 * @param query_hap_chrom: file to read
 * @return match_scores: scores fo each chromosome
 */
vector<pair<string, in>> read_match_file(
    string query_hap_chrom){
    vector<pair<string, int>> match_scores;
    string line;
    ifstream file(query_hap_chrom);
    string header;

    // format
    // MatchID,1,0,1,1,0,0,0,1,0...
    while (getline(file, line)) {
        vector<string> line_vector;
        string matchID;
        vector<int> segment_vector;

        // skip header
        if (header.empty()) {
            header = line;
            continue;
        }

        // split line on ',' and fill line_vector
        stringstream ss(line);
        while (ss.good()) {
            string substr;
            // add each substring to the line-vector
            getline(ss, substr, ',');
            line_vector.push_back(substr);
        }
        
        // get matchID
        matchID = line_vector[0];
        // get segment vector
        for (int i = 1; i < line_vector.size(); i++){
            // try stoi
            try{
                segment_vector.push_back(stoi(line_vector[i]));
            } catch (invalid_argument){
                // if stoi fail, skip
                continue;
            }
        }
        // match ID score = sum of segment vector
        int matchID_score = 0;
        for (auto segment : segment_vector){
            matchID_score += segment;
        }
        match_scores.push_back(make_pair(matchID, matchID_score));
    }
    // sort matches by score
    vector<pair<string, int>> sorted_matches = sort_matches(match_scores);
    return sorted_matches;
}

/*
 * write file for all chromosomes
 * @param out_file: file to write to
 * @param query_ID: query_ID for current file
 * @param chromosome_match_ID_scores: scores for chromosome and match
 */
void write_all_chromosomes(string out_file,
                            string query_ID,
                            map<int, vector<pair<string, int>>> chromosome_match_ID_scores){
    ofstream file(out_file);
    // write header
    file << query_ID << endl;
    file << "Chromosome,MatchID,Score" << endl;
    // for each chromosome
    for (auto const& chromosome : chromosome_match_ID_scores) {
        int chromosome_num = chromosome.first;
        // for each match ID
        for (auto const& match_ID_score : chromosome.second) {
            string match_ID = match_ID_score.first;
            int score = match_ID_score.second;
            file << chromosome_num << "," << match_ID << "," << score << endl;
        }
    }
}


/*
 * Read a file which lists all files in a directory
 * @param sim_search_results_txt: file will all sim_search results in it
 * @return sim_search_results_files: vector of all files with sim_search results
 */
vector<string> read_ss_results_files(
        string ss_results_txt){
    vector<string> ss_results_files;
    ifstream file(ss_results_txt);
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            // if this is not a results file, dont add it to the list
            if (line.find("knn") == string::npos){
                continue;
            }
            ss_results_files.push_back(line);
        }
        file.close();
    }
    else {
        cout << "Unable to open file " << ss_results_txt << endl;
    }
    return ss_results_files;
}

/*
 * Read knn file and add match IDs to map
 * @param filename: name of file to read
 * @param chromosome: chromosome number
 * @param segment: segment number
 * @param query_chromosome_match_ID_segments: map of query ID to chromosome to match IDs to segments
 * @return: void
*/
void read_QCMS(
        string filename,
        int chromosome,
        int segment,
        map<string, map<int, map<string, vector<int>>>> & query_chromosome_match_ID_segments
){
    ifstream file(filename);
    string line;
    string query_ID_line;

    // if file is open, read file line by line
    if (file.is_open()) {
    
        // read file line by line.
        // format:
        // Query: queryID
        // matchID distance
        // matchID distance
        //
        // Query: queryID
        // matchID distance
        // matchID distance
        // ...
    
        while (getline(file, line)) {
        // if "Query: " is found, get query ID
            if (line.find("Query: ") != string::npos) {
                query_ID_line = line;
                query_ID_line = query_ID_line.substr(7);
            }
            // else split the line on tab and add match ID to map
            else {
                string match_ID = line.substr(0, line.find("\t"));
                // if line is empty (last one), skip
                if (match_ID.empty()) {
                    continue;
                }
            
                // if match ID exists, add segment to match ID in map
                if (query_chromosome_match_ID_segments[query_ID_line][chromosome].find(match_ID) !=
                    query_chromosome_match_ID_segments[query_ID_line][chromosome].end()) {
                    query_chromosome_match_ID_segments[query_ID_line][chromosome][match_ID].push_back(segment);
                }
            
                // else add match ID to map
                else{
                    query_chromosome_match_ID_segments[query_ID_line][chromosome][match_ID] = {segment};
                }         
            }
        }
        file.close();
    }
    // if file did not open, print error
    else{
        cout << "Unable to open file " << filename << endl;
    }
}

/*
 * write output for one chromosome
 */
void write_query_output(
        map<int, vector<int>> chromosome_segments,
        map<string, map<int, map<string, vector<int>>>> query_chromosome_match_ID_segments,
        string query_results_dir
        ){
    // for each query make a directory for output
    for (auto const& query : query_chromosome_match_ID_segments) {
        string query_ID = query.first;
        // make directory for this query if it doesn't exist
        
        string query_dir = query_results_dir + query_ID;
        string mkdir_command = "mkdir " + query_dir;
        system(mkdir_command.c_str());

        // for each chromosome write out file
        // format:
        // segment, 0, 1, 2, 3, ...
        // matchID1, 1, 0, 0, 1, ...
        // matchID2, 0, 1, 1, 0, ...
        // ...

        for (auto const& chromosome : query.second) {
            int chromosome_num = chromosome.first;
            string query_chrm_file = query_dir + "/chrm" + to_string(chromosome_num) + ".csv";
            ofstream file(query_chrm_file);
            // write header
            file << "segment,";
            int num_segments = chromosome_segments[chromosome_num].size();
            for (int i = 0; i < num_segments; i++) {
                file << i << ",";
            }
            file << endl;
            // write match IDs
            for (auto const& match_ID : chromosome.second) {
                file << match_ID.first << ",";
                // for each segment in chromosome,
                // write 1 if match ID is in segment,
                // 0 otherwise
                for (int segment : chromosome_segments[chromosome_num]) {
                    if (find(match_ID.second.begin(), match_ID.second.end(), segment) != match_ID.second.end()) {
                        file << "1,";
                    }
                    else {
                        file << "0,";
                    }
                }
                file << endl;
            }
        }
    }
}

