#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
// chronos library can be used to calculate the timestamps

class Vehicle
{
private:
    int rownum;
    int spotnum;
    chrono ::time_point<chrono ::system_clock> parkingstarttime;

public:
    Vehicle()
    {
        rownum = -1;
        spotnum = -1;
    }
    void occupyspot(int r, int c)
    {
        parkingstarttime = chrono::system_clock::now();
        rownum = r;
        spotnum = c;
    }
    void vacatespot()
    {
        rownum = -1;
        spotnum = -1;
    }
    // calculate parking duration in hours using chronos library

    int calculateparkingdurationinhours()
    {
        auto now = chrono::system_clock::now();
        auto duration = chrono::duration_cast<chrono::hours>(now - parkingstarttime);
        return duration.count();
    }
    int calculateparkingfee()
    {
        return 1;
    }
};
class Car : public Vehicle
{
public:
    int parkingfee()
    {
        return 5 * calculateparkingdurationinhours();
    }
    string gettype()
    {
        return "CAR";
    }
};

class Bike : public Vehicle
{
public:
    int parkingfee()
    {
        return 2 * calculateparkingdurationinhours();
    }
    string gettype()
    {
        return "BIKE";
    }
};

class Parking
{
private:
    int rows, spotsperrow;
    vector<vector<Vehicle *>> grid;

public:
    void create(int r, int c)
    {
        rows = r;
        spotsperrow = c;
        grid.resize(r);
        for (int i = 0; i < r; i++)
        {
            grid[i].resize(c);
        }
    }
    pair<int, int> findvacantspot()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < spotsperrow; j++)
            {
                if (grid[i][j] == NULL)
                {
                    return {i, j};
                }
            }
        }
        cout << "NO VALID PARKING SPOT AVAIL !" << endl;
        return {-1, -1};
    }
    bool park(Vehicle *v, int rownum, int spotnum)
    {
        if (grid[rownum][spotnum] != NULL)
        {
            cout << "The parking spot is aldready occupied at : " << rownum << " ," << spotnum << endl;
            return false;
        }
        v->occupyspot(rownum, spotnum);
        grid[rownum][spotnum] = v;
        cout << "You have parked your vehicle at : " << rownum << " ," << spotnum << endl;
        return true;
    }
    bool park(Vehicle *v)
    {
        pair<int, int> spot = findvacantspot();
        if (spot.first >= 0 && spot.second >= 0 && spot.first < rows && spot.second < spotsperrow)
        {
            return park(v, spot.first, spot.second);
        }
        cout << "SORRY NO PARKING AVAILABLE" << endl;
        return false;
    }

    void leave(Vehicle *v)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < spotsperrow; j++)
            {
                if (grid[i][j] == v)
                {
                    grid[i][j] = NULL;
                    int fee = v->calculateparkingdurationinhours();
                    cout << "FEE is RS. " << fee << endl;
                    v->vacatespot();
                }
            }
        }
    }
    void printparking()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < spotsperrow; j++)
            {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
};
int main()
{
    Parking p;
    p.create(3, 2);
    cout << "initially the parking lot :" << endl;
    p.printparking();

    Car c1, c2;
    Bike b1, b2;
    cout << "default parking spot :" << endl;
    p.park(&c1);

    p.printparking();
    p.park(&c2, 1, 1);

    // let the parking system decide where to park the car
    p.printparking();
    p.park(&c2);
    p.printparking();

    p.park(&b1, 2, 1);
    p.printparking();

    p.leave(&c1);
    p.printparking();

    p.leave(&b1);
    p.printparking();

    return 0;
}
