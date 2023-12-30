#ifndef PROJECT_II_FLIGHT_H
#define PROJECT_II_FLIGHT_H

#include <string>

using namespace std;

///Combines hash values of different values into a single hash
/// \param T type of object to hash
/// \param hashSeed current hash seed that is updated
/// \param val the value to hash and combine with the hashSeed
template <class T>
inline void hash_combine(std::size_t& hashSeed, const T& val) {
    hashSeed ^= std::hash<T>{}(val) + 0x9e3779b9 + (hashSeed << 6) + (hashSeed >> 2);
}

class Flight {

private:
    string source_airport_;
    string dest_airport_;
    string airline_;

public:
    ///Flight constructor
    /// \param src_airport Source Airport
    /// \param dest_airport Destination Airport
    /// \param airline Airline operating the flight
    Flight(const string& src_airport, const string& dest_airport,const string& airline);

    size_t operator()(const Flight& flight) const;

    ///Getter function of source_airport_
    /// \return source_airport_
    const string& getSourceAirport() const;

    ///Getter function of dest_airport_
    /// \return dest_airport_
    const string& getDestinationAirport() const;

    ///Getter function of airline_
    /// \return airline_
    const string& getAirline() const;

    ///Operator == overload
    /// \param other Flight used for comparison
    /// return *true* if the current Flight is equal to the Flight other
    bool operator==(const Flight& other) const;

};

#endif //PROJECT_II_FLIGHT_H
