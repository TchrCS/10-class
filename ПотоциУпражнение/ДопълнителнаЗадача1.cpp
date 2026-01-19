/*#include<fstream>
#include<iostream>
#include<sstream>
#include<vector>
#include<algorithm>
using namespace std;

string mostCommonThing(vector<string> vec)
{
    sort(vec.begin(), vec.end());

    string mm;
    int mc = 0;
    string tempM = vec[0];
    int tempC = 1;

    for(int i=0; i < vec.size()-1; i++)
    {
        if(vec[i] == vec[i+1])
        {
            tempC++;
        }
        else
        {
            if(tempC > mc)
            {
                mc = tempC;
                mm = tempM;
                tempC = 1;
                tempM = vec[i+1];
            }
        }
    }

    return mm;
}

int main ()
{
    vector<string> time;
    vector<string> type;
    vector<string> chat;

    fstream file("log.txt");
    ofstream err("error.txt");

    string line;
    while(getline(file, line))
    {
        string lChat;
        bool error = 0;

        stringstream s(line);
        string w;
        for(int i=0; s >> w; i++)
        {
            if(i == 1)
            {
                string t = "";
                t += w[0];
                t += w[1];
                time.push_back(t);
            }
            else if(i == 2)
            {
                type.push_back(w);
                if(w == "ERROR")
                {
                    error++;
                }
            }
            else if(i > 2)
            {
                lChat += w;
                lChat += ' ';
            }
        }

        chat.push_back(lChat);

        if(error)
        {
            err << line << "\n";
        }
    }

    err.close();
    file.close();

    /// types

    cout<<"The most common type is: "<<mostCommonThing(type)<<endl<<endl;

    /// messages

    cout<<"The most common message is: "<<mostCommonThing(chat)<<endl<<endl;

    /// hour

    cout<<"The most common hour is: "<<mostCommonThing(time)<<endl<<endl;
    return 0;
}
*/

/*

    the following codeblock is for the problem author

    rage and wrath be upon the AI images, homework for you from me is to find out
    why they are morally bad, who they affect and their energy consequences

    stupid problems, do better next time :3

    Meh attempt at storytelling, take a look at https://adventofcode.com/
    for a properly done christmas story

    complaints from people that aren't me:
        1) "I want problems i have to think about"
        2) "this is just hamalene"

    regarding 1), it is addressed by 5. from the problem - "the great algorithm"
    However the difficulty jump is insane. Multi-objective constrained optimization
    is not within their reach. Nor mine to be fair

    spelling mistake on 2. v fail -> vUV fail
*/

#include<iostream>
#include<fstream>
#include<string>
#include<vector> // yes complain to me about this
#include<limits>
#include<unordered_set>
using namespace std;

const string SEPARATOR = ",",
             SAVE_FILE_NAME = "stable.csv",
             TEAM_FILE_NAME = "optimal_harness.csv";

struct Reindeer{
    string name;
    double maxSpeed, stamina, strength;
    bool wearsBells;

    void print(){
        cout << "Name        :" << name << endl;
        cout << "Max Speed   :" << maxSpeed << endl;
        cout << "Stamina     :" << stamina << endl;
        cout << "Strength    :" << strength << endl;
        cout << "Bells (0/1) :" << wearsBells << endl;
    }

    string toString(){
        return name + SEPARATOR +
              to_string(maxSpeed) + SEPARATOR +
              to_string(stamina) + SEPARATOR +
              to_string(strength) + SEPARATOR +
              (wearsBells ? "1" : "0");
    }

    void fromString(string str){
        int i = 0, last_separator = -1, field = 0;
        while(i < str.size()){
            if(str[i] == SEPARATOR[0] || i + 1 >= str.size()){
                string s = str.substr(last_separator + 1, i - last_separator - 1 + (i + 1 >= str.size()));
                if(field == 0){
                    name = s;
                }else if(field == 1){
                    maxSpeed = stod(s);
                }else if(field == 2){
                    stamina = stod(s);
                }else if(field == 3){
                    strength = stod(s);
                }else{
                    wearsBells = stoi(s);  // 0 or 1 are valid bool values
                }
                last_separator = i;
                field++;
            }
            i++;
        }
    }
};

// purely DB actions in the DB struct
struct DB{
    vector<Reindeer> reindeer; // single source of truth
    vector<int> optimal_team;

    void addDeer(Reindeer deer){
        reindeer.push_back(deer);
    }

    // isFound, deer
    pair<bool, Reindeer> searchByName(string name){
        for(Reindeer deer : reindeer){
            if(deer.name == name) return {true, deer};
        }
        Reindeer d;
        return {false, d};
    }

    bool saveToCSV(){
        ofstream io(SAVE_FILE_NAME);
        if(!io) return false;
        for(auto deer : reindeer){
            io << deer.toString() << "\n";
        }
        return true;
    }

    bool saveTeamToCSV(){
        ofstream io(TEAM_FILE_NAME);
        if(!io) return false;
        for(int i : optimal_team){
            io << reindeer[i].toString() << "\n";
        }
        return true;
    }

    bool loadFromCSV(){
        ifstream io(SAVE_FILE_NAME);
        if(!io) return false;
        reindeer.clear(); // clear only after file has been opened
        string s;
        while(getline(io, s)){
            Reindeer d;
            d.fromString(s);
            reindeer.push_back(d);
        }
        return true;
    }

    void setTeam(tuple<int, int, int, int, int, int> t){
        optimal_team = {
            std::get<0>(t),
            std::get<1>(t),
            std::get<2>(t),
            std::get<3>(t),
            std::get<4>(t),
            std::get<5>(t)
        };
    }

    void findTeam(double weight, double speed){
        // be thankfull I didn't use std::next_permutation() on the deer vector
        int sz = reindeer.size();
        bool hasSetTeam = false;
        double bestAverageSpeed, bestTotalStamina;

        for(int a = 0; a < sz; ++a){
            for(int b = a + 1; b < sz; ++b){
                for(int c = b + 1; c < sz; ++c){
                    for(int d = c + 1; d < sz; ++d){
                        for(int e = d + 1; e < sz; ++e){
                            for(int f = e + 1; f < sz; ++f){
                                unordered_set<int> s;
                                s.insert(a);
                                s.insert(b);
                                s.insert(c);
                                s.insert(d);
                                s.insert(e);
                                s.insert(f);
                                if(s.size() < 6) continue;
                                if(!(a < b && b < c && c < d && d < e && e < f)) continue;
                                // we now have 6 different deer from the array
                                Reindeer deer[6];
                                deer[0] = reindeer[a];
                                deer[1] = reindeer[b];
                                deer[2] = reindeer[c];
                                deer[3] = reindeer[d];
                                deer[4] = reindeer[e];
                                deer[5] = reindeer[f];
                                double totalStrength = 0, totalSpeed = 0, totalStamina = 0;
                                for(auto d : deer){ // wait this works??
                                    totalStrength += d.strength;
                                    totalSpeed += d.maxSpeed;
                                    totalStamina += d.stamina;
                                }
                                if(totalStrength - weight < 1e-6){ // assuming 0 air friction
                                    continue; // sleight is too heavy
                                }
                                double avgSpeed = totalSpeed / 6.0;
                                if(!hasSetTeam){
                                    hasSetTeam = true;
                                    bestAverageSpeed = avgSpeed;
                                    bestTotalStamina = totalStamina;
                                    setTeam({a, b, c, d, e, f});
                                    continue;
                                }
                                    // closeness
                                double bestTeamCloseness = abs(bestAverageSpeed - speed), currTeamCloseness = abs(avgSpeed - speed);
                                if(abs(bestTeamCloseness - currTeamCloseness) < 1e-6){ // equal
                                    if(totalStamina - bestTotalStamina < 1e-6){
                                    bestAverageSpeed = avgSpeed;
                                    bestTotalStamina = totalStamina;
                                    setTeam({a, b, c, d, e, f});
                                    }
                                }else if(currTeamCloseness - bestTeamCloseness < 1e-6){ // curr team is closer
                                    bestAverageSpeed = avgSpeed;
                                    bestTotalStamina = totalStamina;
                                    setTeam({a, b, c, d, e, f});
                                }
                            }
                        }
                    }
                }
            }
        }
    }
};

DB db;

Reindeer getReindeerFromUser(){
    Reindeer deer;
    cout << "Name        :"; getline(cin, deer.name);
    cout << "Max Speed   :"; cin >> deer.maxSpeed;
    cout << "Stamina     :"; cin >> deer.stamina;
    cout << "Strength    :"; cin >> deer.strength;
    cout << "Bells (0/1) :"; cin >> deer.wearsBells;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer cuz mixing getline and cin is evil
    return deer;
}

int main(){
    int action; // obligatory ASCII ART
    cout << " ####  ###  #   # #####  ###        ####  #### " << endl;
    cout << "#     #   # ##  #   #   #   #       #   # #   #" << endl;
    cout << " ###  ##### # # #   #   #####       #   # #### " << endl;
    cout << "    # #   # #  ##   #   #   #       #   # #   #" << endl;
    cout << "####  #   # #   #   #   #   #       ####  #### " << endl;
    while(true){
        cout << endl;
        cout << "1 - Register a deer" << endl;
        cout << "2 - Save" << endl;
        cout << "3 - Load" << endl;
        cout << "4 - Search deer by name" << endl;
        cout << "5 - Epic algorithm or smth" << endl;
        cout << "6 - Save 5" << endl;
        cout << "7 - Quit" << endl;
        cout << "Command: ";
        cin >> action;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch(action){
            case 1:
                db.addDeer(getReindeerFromUser());
                break;
            case 2:
                cout << "Saving... ";
                if(db.saveToCSV()){
                    cout << "Saved!";
                }else{
                    cout << "Error saving";
                }
                cout << endl;
                break;
            case 3:
                cout << "Loading... ";
                if(db.loadFromCSV()){
                    cout << "Loaded!";
                }else{
                    cout << "Error loading";
                }
                cout << endl;
                break;
            case 4:
                {
                    string name;
                    cout << "Name to search for: "; getline(cin, name);
                    pair<bool, Reindeer> result = db.searchByName(name);
                    if(result.first){
                        cout << "Deer found!" << endl;
                        result.second.print();
                    }else{
                        cout << "Reindeer not found. Perhaps it's on a practice flight!" << endl;
                    }
                }
                break;
            case 5:
                // fuck you and whatever this bullshit is
                {
                    double weight, speed;
                    cout << "Sleigh weight: "; cin >> weight;
                    cout << "Target speed : "; cin >> speed;
                    cout << "Calculating... ";
                    db.findTeam(weight, speed);
                    cout << "Found the optimal team!" << endl;
                }
            case 6:
                cout << "Saving... ";
                if(db.saveTeamToCSV()){
                    cout << "Saved!";
                }else{
                    cout << "Error saving";
                }
                cout << endl;
                break;
            case 7:
                cout << "bye bye";
                return 0;
            default:
                cout << "TAPAK OPITAI PAK" << endl;
                break;
        }
    }
    return 0;
}
