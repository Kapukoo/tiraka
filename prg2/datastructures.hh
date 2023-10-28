// Datastructures.hh
//
// Student name: Kasper Kivistö
// Student email: kasper.kivisto@tuni.fi
// Student number: 50302871

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <exception>
#include <map>
#include <set>


// Types for IDs
using StationID = std::string;
using TrainID = std::string;
using RegionID = unsigned long long int;
using Name = std::string;
using Time = unsigned short int;

// Return values for cases where required thing was not found
StationID const NO_STATION = "---";
TrainID const NO_TRAIN = "---";
RegionID const NO_REGION = -1;
Name const NO_NAME = "!NO_NAME!";
Time const NO_TIME = 9999;

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();


// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};

// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Type for a distance (in metres)
using Distance = int;

// Return value for cases where Distance is unknown
Distance const NO_DISTANCE = NO_VALUE;

// This exception class is there just so that the user interface can notify
// about operations which are not (yet) implemented
class NotImplemented : public std::exception
{
public:
    NotImplemented() : msg_{} {}
    explicit NotImplemented(std::string const& msg) : msg_{msg + " not implemented"} {}

    virtual const char* what() const noexcept override
    {
        return msg_.c_str();
    }
private:
    std::string msg_;
};


// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance: O(1)
    // Short rationale for estimate: return only vector.
    unsigned int station_count();

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: CPP reference for clear() x6.
    void clear_all();

    // Estimate of performance: O(n)
    // Short rationale for estimate: returns only one vector.
    std::vector<StationID> all_stations();

    // Estimate of performance: O(log(n))
    // Short rationale for estimate: many log(n) operations in series.
    bool add_station(StationID id, Name const& name, Coord xy);

    // Estimate of performance: O(1)
    // Short rationale for estimate: 2 times []-operator on unorder_map.
    Name get_station_name(StationID id);

    // Estimate of performance: O(1)
    // Short rationale for estimate: 2 times []-operator on unorder_map.
    Coord get_station_coordinates(StationID id);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n)
    // Short rationale for estimate: one for loop and reserving before looping.
    std::vector<StationID> stations_alphabetically();

    // Estimate of performance: O(n)
    // Short rationale for estimate: one for loop and reserving before looping.
    std::vector<StationID> stations_distance_increasing();

    // Estimate of performance: O(log(n))
    // Short rationale for estimate: two []-operations on unordered_map
    StationID find_station_with_coord(Coord xy);

    // Estimate of performance: O(log(n))
    // Short rationale for estimate: several []-operations. log(n) each.
    bool change_station_coord(StationID id, Coord newcoord);

    // Estimate of performance: O(n)
    // Short rationale for estimate: several []-operations. log(n) each.
    bool add_departure(StationID stationid, TrainID trainid, Time time);

    // Estimate of performance: O(log(n))
    // Short rationale for estimate: several []-operations. log(n) each.
    bool remove_departure(StationID stationid, TrainID trainid, Time time);

    // Estimate of performance: O(n*log(n))
    // Short rationale for estimate: several []-operations. log(n) each and find_if.
    std::vector<std::pair<Time, TrainID>> station_departures_after(StationID stationid, Time time);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(log(n))
    // Short rationale for estimate: 3 times []-operations each log(n).
    bool add_region(RegionID id, Name const& name, std::vector<Coord> coords);

    // Estimate of performance: O(n)
    // Short rationale for estimate: one for loop.
    std::vector<RegionID> all_regions();

    // Estimate of performance: O(log(n))
    // Short rationale for estimate: 2 times []-operations each log(n).
    Name get_region_name(RegionID id);

    // Estimate of performance: O(log(n))
    // Short rationale for estimate: 2 times []-operations each log(n).
    std::vector<Coord> get_region_coords(RegionID id);

    // Estimate of performance: O(n*log(n))
    // Short rationale for estimate: for loop and []-operands.
    bool add_subregion_to_region(RegionID id, RegionID parentid);

    // Estimate of performance: O(log(n))
    // Short rationale for estimate: 3 times []-operations each log(n).
    bool add_station_to_region(StationID id, RegionID parentid);

    // Estimate of performance: O(n*log(n))
    // Short rationale for estimate: []-operand and while loop.
    std::vector<RegionID> station_in_regions(StationID id);

    // Non-compulsory operations

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: for-loop and recursion -> many n operations.
    std::vector<RegionID> all_subregions_of_region(RegionID id);

    // Estimate of performance: O(n*log(n))
    // Short rationale for estimate: one for-loop and max 3 element for loop.
    std::vector<StationID> stations_closest_to(Coord xy);

    // Estimate of performance: O(n*log(n))
    // Short rationale for estimate: for-loop and many erase operations.
    bool remove_station(StationID id);

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: for-loop and all_subregions_of_region-function.
    RegionID common_parent_of_regions(RegionID id1, RegionID id2);

    //
    // New assignment 2 operations
    //

    // Estimate of performance: O(n*log(n))
    // Short rationale for estimate: []-operations and one for loop.
    bool add_train(TrainID trainid, std::vector<std::pair<StationID, Time>> stationtimes);

    // Estimate of performance: O(n*log(n))
    // Short rationale for estimate: []-operations and one for loop.
    std::vector<StationID> next_stations_from(StationID id);

    // Estimate of performance: O(n*log(n))
    // Short rationale for estimate: []-operations and one for loop.
    std::vector<StationID> train_stations_from(StationID stationid, TrainID trainid);

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: two for loops and clear()-operations.
    void clear_trains();

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: several while and for loops.
    std::vector<std::pair<StationID, Distance>> route_any(StationID fromid, StationID toid);

    // Non-compulsory operations

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: it happens to be the same function as route_any
    std::vector<std::pair<StationID, Distance>> route_least_stations(StationID fromid, StationID toid);

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: several while and for loops
    std::vector<StationID> route_with_cycle(StationID fromid);

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: several while and for loops
    std::vector<std::pair<StationID, Distance>> route_shortest_distance(StationID fromid, StationID toid);

    // Estimate of performance: O( )
    // Short rationale for estimate: this function is not implemented
    std::vector<std::pair<StationID, Time>> route_earliest_arrival(StationID fromid, StationID toid, Time starttime);

private:
    // Add stuff needed for your class implementation here

    // test functions
    bool test_station(StationID& id);
    bool test_region(RegionID& id);
    // prg2
    double distance(StationID from, StationID to);

    // station info struct
    struct Station_info
    {
        Name name_ = NO_NAME;
        RegionID regionID_ = NO_REGION;
        Coord coord_ = NO_COORD;
        std::set<std::pair<Time, TrainID>> departure_info;
        RegionID belongs_to_reg = NO_REGION;
    };
    // all station data is saved in this map
    std::unordered_map<StationID, Station_info> station_data;

    // all station id's for fast use
    std::vector<StationID> station_ids_vector;
    // map for alphabetical order
    std::map<Name, StationID> stations_in_name_order;
    // multiset for length ordering
    std::multiset<std::pair <double, std::pair<int, StationID> > > stations_in_lenght;
    // map for searching with coord
    std::map<Coord, StationID> map_coord_id;



    // region info struct
    struct Region_info
    {
        Name regname_ = NO_NAME;
        std::vector<Coord> regcoords_;
        RegionID father = NO_REGION;
        std::vector<RegionID> children;
    };
    // all region info is stored in this map
    std::unordered_map<RegionID,Region_info> region_data;

    //---prg2---

    // specific train's route and schedule
    std::unordered_map<TrainID, std::vector<std::pair<StationID, Time>> > train_data;
    // station's neighbour stations
    std::unordered_map<StationID, std::set<StationID>> station_neighbours;




};

#endif // DATASTRUCTURES_HH
