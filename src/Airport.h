#ifndef PROJECT_II_AIRPORT_H
#define PROJECT_II_AIRPORT_H

#include <string>
#include <iostream>
#include <cmath>

using namespace std;

struct position {
    double latitude;
    double longitude;

    bool operator==(const position& other) const {
        return latitude == other.latitude && longitude == other.longitude;
    }
};

/// Class that represents an Airport
class Airport {

private:
    string airport_code_;
    string airport_name_;
    string airport_city_;
    string airport_country_;
    position airport_position_;

public:

    /// Airport Default Constructor
    Airport();

    ///Airport Constructor with position struct
    ///
    /// \param airport_code Airport unique code
    /// \param airport_name Airport name
    /// \param airport_city Airport city location
    /// \param airport_country Airport country location
    /// \param airport_position Airport position coordinates
    Airport(const string& airport_code, const string& airport_name="", const string& airport_city="",const string& airport_country="", const position& airport_position={0,0});


    ///Airport Constructor with latitude and longitude coordinates
    ///
    /// \param airport_code Airport unique code
    /// \param airport_name Airport name
    /// \param airport_city Airport city location
    /// \param airport_country Airport country location
    /// \param latitude Airport latitude coordinate
    /// \param longitude Airport longitude coordinate
    Airport(const string& airport_code, const string& airport_name, const string& airport_city,const string& airport_country, double latitude, double longitude);

    ///Getter function of airport_code_
    /// \return airport_code_
    const string& getAirportCode() const;

    ///Getter function of airport_name_
    /// \return airport_name_
    const string& getAirportName() const;

    ///Getter function of airport_city_
    /// \return airport_city_
    const string& getAirportCity() const;

    ///Getter function of airport_country_
    /// \return airport_country_
    const string& getAirportCountry() const;

    ///Getter function of airport_position_
    /// \return airport_position_
    const position& getAirportPosition() const;

    ///Function that prints the coordinates of the airport position
    void printAirportPosition() const;

    ///Operator < overload
    /// \param other Airport used for comparation
    /// return *true* if the current Airport code is lower alphabetically
    bool operator<(const Airport& other) const;

    /**
     * @brief Equality comparison operator for Airport objects.
     *
     * This operator checks if the current Airport object is equal to another Airport object.
     * Two airports are considered equal if their airport codes are the same (unique names)
     */
    bool operator==(const Airport& other) const;

    ///Obtains the distance between the airport and a given position, using the Harvesine formula
    ///Time Complexity: O(1)
    /// \param position Position whose distance we wish to know
    /// \return distance between airport and position
    double distance(position position);
};

#endif //PROJECT_II_AIRPORT_H
