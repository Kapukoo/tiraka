// Datastructures.cc
//
// Student name: Kasper Kivistö
// Student email: kasper.kivisto@tuni.fi
// Student number: 50302871

#include "datastructures.hh"

#include <random>
#include <algorithm>
#include <cmath>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)


//------------------first part--------------------------------


Datastructures::Datastructures()
{
    // Write any initialization you need here
}

Datastructures::~Datastructures()
{
    // Write any cleanup you need here
}

/**
 * @brief station_count returns number of stations
 * @return number of stations
 */
unsigned int Datastructures::station_count()
{
    return station_data.size();
}

/**
 * @brief clear_all clears all data structures
 */
void Datastructures::clear_all()
{
    station_data.clear();
    station_ids_vector.clear();
    stations_in_name_order.clear();
    stations_in_lenght.clear();
    map_coord_id.clear();

    region_data.clear();
    return;
}

/**
 * @brief all_stations returns all stations
 * @return all stations in a vector
 */
std::vector<StationID> Datastructures::all_stations()
{
    return station_ids_vector;
}

/**
 * @brief test_station tests if the station exists
 * @param station to test
 * @return true if found / false if not found
 */
bool Datastructures::test_station(StationID& id){
    if (station_data.find(id) != station_data.end()){
        return true;
    }
    else {return false;}
}

/**
 * @brief test_region tests if the region exists
 * @param region to test
 * @return true not found / false if not found
 */
bool Datastructures::test_region(RegionID& id){
    if (region_data.find(id) != region_data.end()){
        return true;
    }
    else {return false;}
}

/**
 * @brief add_stations adds a new station in the data structure
 * @param id station's id
 * @param name station's name
 * @param xy station's coordinates
 * @return true if success / false if station already exists
 */
bool Datastructures::add_station(StationID id, const Name& name, Coord xy)
{
    if ( test_station(id) == false ){

        // station_data mpa
        station_data[id].name_=name;
        station_data[id].coord_ = xy;
        station_ids_vector.push_back(id);

        // In name order
        stations_in_name_order[name] = id;

        // in length order
        double length = sqrt(xy.x*xy.x + xy.y*xy.y);
        stations_in_lenght.insert(make_pair(length, make_pair(xy.y,id)));

        // for searchind id with coord;
        map_coord_id[xy] = id;

        return true;

    }
    else {
        return false;
    }

}

/**
 * @brief get_station_name return the name of station id
 * @param station's id we want the name of
 * @return stations name / NO_NAME if no station found
 */
Name Datastructures::get_station_name(StationID id)
{
    if ( test_station(id) ){
        return station_data[id].name_;
    }
    return NO_NAME;
}

/**
 * @brief get_station_coordinates return stations coordinates
 * @param station's id we want the coordinates of
 * @return station's coordinates
 */
Coord Datastructures::get_station_coordinates(StationID id)
{
    if ( test_station(id) ){
        return station_data[id].coord_;
    }
    return NO_COORD;
}


// -------------second part-------------------

/**
 * @brief stations_alphabetically returns all the stations in alphabetical order
 * @return vector with stations in alphabetical order
 */
std::vector<StationID> Datastructures::stations_alphabetically()
{
    int vec_size = stations_in_name_order.size();
    std::vector<StationID> v;
    v.resize(vec_size); // resizing vector to eliminate reallocation
    int i = 0;

    for (auto ID : stations_in_name_order){
        v[i] = ID.second;
        i++;
    }
    return v;
}


/**
 * @brief stations_distance_increasing returns stations in increasing order of distance from (0,0)
 * @return vector with station ids in increasing order
 */
std::vector<StationID> Datastructures::stations_distance_increasing()
{

    int vec_size = stations_in_lenght.size();
    std::vector<StationID> v;
    v.reserve(vec_size);

    for (auto x : stations_in_lenght){
        v.emplace_back(x.second.second);
    }
    return v;
}

/**
 * @brief find_station_with_coord finds station with given coordinates
 * @param xy coordinates to find stationd id with
 * @return station id found wiht coords
 */
StationID Datastructures::find_station_with_coord(Coord xy)
{
    if ( map_coord_id.find(xy) != map_coord_id.end() ){
         return map_coord_id[xy];
    }
    return NO_STATION;
}

/**
 * @brief change_station_coord changes stations coordinates
 * @param id station to change coords of
 * @param newcoord stations new coords
 * @return true if success / false if no station found
 */
bool Datastructures::change_station_coord(StationID id, Coord newcoord)
{
    if ( test_station(id) ){
        // id found
        Coord xy = station_data[id].coord_; // old coord
        double length = sqrt(xy.x*xy.x + xy.y*xy.y); // old length

        // deleting old data
        std::pair <double, std::pair<int, StationID> > pair_delete;
        pair_delete = make_pair(length, make_pair(xy.y,id));
        stations_in_lenght.erase(pair_delete);

        map_coord_id.erase(xy);

        // inserting new data
        station_data[id].coord_ = newcoord;
        double nlength = sqrt(newcoord.x*newcoord.x + newcoord.y*newcoord.y);
        stations_in_lenght.insert(make_pair(nlength, make_pair(newcoord.y,id)));

        station_data[id].coord_=newcoord;
        map_coord_id[newcoord] = id;

        return true;
    }
    return false;
}

/**
 * @brief add_departure add new departure
 * @param stationid station to add departure to
 * @param trainid departures train id
 * @param time departures time
 * @return true if success / false if no station found
 */
bool Datastructures::add_departure(StationID stationid, TrainID trainid, Time time)
{
    if ( test_station(stationid) ){
        // id found
        auto &depinfo = station_data[stationid].departure_info;
        std::pair departure = {time, trainid};

        if ( depinfo.find(departure) != depinfo.end()){
            // departure found -> skip
            return false;
        }
        // not found -> adding
        depinfo.insert(departure);
        return true;
        }

    // no id
    return false;
}

/**
 * @brief remove_departure removes given departure
 * @param stationid station of departure
 * @param trainid departures train id
 * @param time departures time
 * @return true if success / false if no station or departure
 */
bool Datastructures::remove_departure(StationID stationid, TrainID trainid, Time time)
{
    if ( test_station(stationid) ){
        // id found
        auto &depinfo = station_data[stationid].departure_info;
        std::pair departure_del = {time, trainid};

        if ( depinfo.find(departure_del) != depinfo.end() ){
            // departure found -> deleting
            depinfo.erase(departure_del);
            return true;
        }
        // no departure found
        return false;
    }
    // no id
    return false;
}

/**
 * @brief station_departures_after return departures from station after time
 * @param stationid station of intrest
 * @param time of instrest
 * @return vector of times and train ids after specific time
 */
std::vector<std::pair<Time, TrainID>> Datastructures::station_departures_after(StationID stationid, Time time)
{

    if ( test_station(stationid) ){
        // id found
        std::vector<std::pair<Time, TrainID>> v;
        auto &depinfo = station_data[stationid].departure_info;

        auto it = std::find_if(depinfo.begin(), depinfo.end(),
                               [time](const std::pair<Time, TrainID>& p)
                                {return p.first >= time; });

        v = {it, depinfo.end()};
        return v;
    }
    // no id
    return {{NO_TIME,NO_TRAIN}};
}


// ----------------kolmas osa---------------------


/**
 * @brief add_region add new region
 * @param id regions id
 * @param name regions name
 * @param coords regions coordinates
 * @return true if success / false if no region found
 */
bool Datastructures::add_region(RegionID id, const Name &name, std::vector<Coord> coords)
{
    if (test_region(id) == false){
        // no regiond -> adding
        region_data[id].regname_ = name;
        region_data[id].regcoords_ = coords;
        return true;
    }
    // region found -> skip
    return false;
}

/**
 * @brief all_regions return all region ids
 * @return vector if regionIDs
 */
std::vector<RegionID> Datastructures::all_regions()
{
    std::vector<RegionID> v;
    for (auto x : region_data){
        v.push_back(x.first);
    }
    return v;
}

/**
 * @brief get_region_name gets region's name
 * @param id region of intrest
 * @return region's name
 */
Name Datastructures::get_region_name(RegionID id)
{
    if ( test_region(id) ){
        // region found
        return region_data[id].regname_;
    }
    return NO_NAME;
}

/**
 * @brief get_region_coords get's region's coordinates
 * @param id region's id
 * @return region's coords
 */
std::vector<Coord> Datastructures::get_region_coords(RegionID id)
{
    if ( test_region(id) ){
        // region found
        return region_data[id].regcoords_;
    }
    // no region found
    return {NO_COORD};
}

/**
 * @brief add_subregion_to_region add subregion to region
 * @param id subregion's id
 * @param parentid parent region's id
 * @return true if success / false if no region found or already added
 */
bool Datastructures::add_subregion_to_region(RegionID id, RegionID parentid)
{
    if ( test_region(id) ){
        //region found

        if ( test_region(id) ){
            // parent found
            for (auto x : region_data[parentid].children){
                if (x == id){
                    // subregion already added -> skip
                    return false;
                }
            }
            // no subregion -> adding
            region_data[parentid].children.push_back(id);
            region_data[id].father = parentid;
            return true;
        }

        // no parent found
        return false;
    }
    // no region found
    return false;
}

/**
 * @brief add_station_to_region add station to region
 * @param id station' id
 * @param parentid region's id
 * @return true if success / false if no region or already added
 */
bool Datastructures::add_station_to_region(StationID id, RegionID parentid)
{
    if ( test_region(parentid) ){
        // parent found

        if ( test_station(id) ){
            // id found
            if (station_data[id].belongs_to_reg != NO_REGION){
                // station already in region -> skip
                return false;
            }
            // no region -> adding
            station_data[id].belongs_to_reg = parentid;
            return true;
        }

        // id not found
        return false;
    }
    // no parent found
    return false;
}

/**
 * @brief station_in_regions returns all stations in regions
 * @param id region's id
 * @return vector of region ids
 */
std::vector<RegionID> Datastructures::station_in_regions(StationID id)
{
    if ( test_station(id) ){
        // id found
        std::vector<RegionID> v;
        // main region info
        RegionID mainreg = station_data[id].belongs_to_reg;
        if (mainreg != NO_REGION){
            v.push_back(mainreg);
        }
        else {
            return {};
        }

        // mainregion parents
        while(true){
            RegionID sub_reg_of = region_data[mainreg].father;
            if ( sub_reg_of != NO_REGION){
                // parent found
                mainreg = sub_reg_of;
                v.push_back(mainreg);
            }
            else {break;}
        }

        return v;
    }
    else {
        // id not found
        return {NO_REGION};
    }

}


//------------------ei pakolliset-----------------------


/**
 * @brief all_subregions_of_region returns all subregions of region
 * @param id region's id
 * @return vector of region ids
 */
std::vector<RegionID> Datastructures::all_subregions_of_region(RegionID id)
{
    if ( test_region(id) ){
        // id found
        std::vector<RegionID> v;
        if (region_data[id].children.size() > 0){
            // region has subregions
            for (auto x : region_data[id].children){
                // push back x
                v.push_back(x);
                // x's subregions in recursion
                std::vector<RegionID> rekursio = all_subregions_of_region(x);
                v.insert(v.end(), rekursio.begin(), rekursio.end());

            }
        }
        return v;
    }
    // no id found
    return {NO_REGION};
}

/**
 * @brief stations_closest_to returns 3 closest stations to given coordinations
 * @param xy given coordinates
 * @return vector of station ids
 */
std::vector<StationID> Datastructures::stations_closest_to(Coord xy)
{
    std::vector<StationID> v;
    std::multiset<std::pair <double, std::pair<int, StationID> > > inorder;

    for ( auto P : map_coord_id ){
        Coord ab = P.first;
        double length = sqrt( pow(xy.x-ab.x, 2) + pow(xy.y-ab.y,2) );

        inorder.insert( {length, {ab.y, P.second}} );
    }

    int i = 0;
    for ( auto x : inorder ){
        if ( i >= 3 ){
            break;
        }
        v.push_back(x.second.second);
        i++;
    }

    return v;
}

/**
 * @brief remove_station remove given station
 * @param id station's id
 * @return true if success / false if no station found
 */
bool Datastructures::remove_station(StationID id)
{
    if ( test_station(id) ){
        // id found
        Coord xy = station_data[id].coord_;
        Name name = station_data[id].name_;
        // deletion
        station_data.erase(id);

        for ( unsigned int i = 0; i < station_ids_vector.size(); i++){
            if ( station_ids_vector[i] == id ){
                station_ids_vector.erase(station_ids_vector.begin() + i);
            }
        }

        stations_in_name_order.erase(name);

        double length = sqrt(xy.x*xy.x + xy.y*xy.y);
        stations_in_lenght.erase( make_pair(length,make_pair(xy.y,id)) );

        map_coord_id.erase(xy);

        return true;
    }
    return false;
}

/**
 * @brief common_parent_of_regions returns the parent region of two regions
 * @param id1 regiond 1
 * @param id2 region 2
 * @return parent region of regiond 1 and 2
 */
RegionID Datastructures::common_parent_of_regions(RegionID id1, RegionID id2)
{
    if ( test_region(id1) ){
        if ( test_region(id2) ){
            // both ids found
            RegionID current = region_data[id1].father;
            while (true){

                if ( current == NO_REGION){
                    break;
                }
                // current region and it's subregions
                std::vector<RegionID> subregions = all_subregions_of_region(current);

                for ( auto x : subregions ){
                    if ( x == id2 ){
                        return current;
                    }
                }
                // no id2 found -> up one level
                current = region_data[current].father;

            }
            //
        }
    }
    return NO_REGION;

}


