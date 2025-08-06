#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <SFML/Graphics.hpp>
#include <cmath> 
using namespace std;


#define RESET   "\033[0m"      // Reset color to default
#define BLACK   "\033[30m"     // Black
#define RED     "\033[31m"     // Red
#define GREEN   "\033[32m"     // Green
#define YELLOW  "\033[33m"     // Yellow
#define BLUE    "\033[34m"     // Blue
#define MAGENTA "\033[35m"     // Magenta
#define CYAN    "\033[36m"     // Cyan
#define WHITE   "\033[37m"     // White



class Flight  //flight class to store the imformation abour a certain flight
{
public:
    string origin;
    string destination;
    string airline;
    string date;
    string departureTime;
    string arrivalTime;
    string duration;
    float price;


    Flight* next;

    // constructor
    Flight(string origin, string destination, string airline, string date, string depTime, string arrTime, float price, string dur)
        : origin(origin), destination(destination), airline(airline), date(date), departureTime(depTime), arrivalTime(arrTime), price(price), next(nullptr), duration(dur)
    {}
};

class CityNode    // class to represent a city with associated flights
{
public:
    string cityName;
    Flight* flights;
    CityNode* next;
    float hotelCharge;


    CityNode(string name = " ", float charge = 0.0) : cityName(name), flights(NULL), next(NULL), hotelCharge(charge) {}


    void addFlight(Flight* newFlight)
    {
        if (flights == NULL)
        {
            flights = newFlight;
        }
        else
        {
            Flight* temp = flights;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newFlight;
        }
    }


    Flight* findFlightTo(const string& destination)   //finding adn then returning, flight to a specific destination
    {
        Flight* temp = flights;
        while (temp != nullptr)
        {
            if (temp->destination == destination)
            {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }
};

class BookedFlight        //deal with flights that have been booked 
{
public:
    Flight* flight;//the booked flight 
    BookedFlight* next;   //pointer to next booked flight


    BookedFlight(Flight* f) : flight(f), next(nullptr)
    {}
};

class Stack       //stack class for easy depth traversal 
{
private:
    struct Node    //private struct to use node inside this stack
    {
        CityNode* data;
        Node* next;
    };
    Node* top;


public:
    Stack() : top(nullptr)
    {}

    ~Stack() {
        while (!isEmpty())
        {
            pop();     //emptying stack
        }
    }

    bool isEmpty()
    {
        return top == nullptr;
    }

    void push(CityNode* city)
    {
        Node* newNode = new Node{ city, top };
        top = newNode;
    }

    CityNode* pop()
    {
        if (isEmpty())
        {
            return nullptr;
        }
        Node* temp = top;
        CityNode* data = top->data;
        top = top->next;
        delete temp;
        return data;
    }

    CityNode* peek()
    {
        if (isEmpty())
        {
            return nullptr;
        }
        return top->data;
    }

    bool isPresent(string& city)     //checjing if a certain city is present in stack 
    {
        Node* newNode = top;

        while (newNode)
        {
            if (newNode->data->cityName == city)      //if the stack contains the desired city name return true
            {
                return true;
            }

            newNode = newNode->next;
        }
        return false;

    }
};

class VisitedList        //to check if a city has already been visited during traversal 
{
private:
    struct Node       //private struct to use node inside this list
    {
        string cityName;
        Node* next;
    };
    Node* head;

public:
    VisitedList() : head(nullptr)
    {}

    ~VisitedList()
    {
        while (head)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    bool isVisited(const string& cityName)     //to check if a city is already visited or not 
    {
        Node* current = head;
        while (current)
        {
            if (current->cityName == cityName)
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void addVisited(const string& cityName)     //if a city isnt visited add it
    {
        if (!isVisited(cityName))
        {
            Node* newNode = new Node{ cityName, head };     //making new nodes in list to store not visited cities
            head = newNode;
        }
    }

    void display()
    {
        Node* newNode = head;
        while (newNode) {
            cout << newNode->cityName << endl;
            newNode = newNode->next;
        }
    }
};

template <typename T>   //using templates so that the class can operate on any data type, making the code more reusable and flexible
class CustomQueue   //badically using it to find connections
{
private:
    struct Node    //priv struct to sue node on this queue
    {
        T data;
        Node* next;
        Node(const T& value, Node* nextNode = nullptr) : data(value), next(nextNode) {}
    };
    Node* frontNode;
    Node* backNode;

public:
    CustomQueue()
    {
        frontNode = nullptr;
        backNode = nullptr;
    }

    CustomQueue(const CustomQueue& other)     //copy constructor 
    {
        frontNode = nullptr;
        backNode = nullptr;
        Node* current = other.frontNode;
        while (current)
        {
            push(current->data);
            current = current->next;
        }

    }
    ~CustomQueue()
    {
        while (!isEmpty())
        {
            pop();
        }
    }

    void push(const T& value)     //adding a new element 
    {
        Node* newNode = new Node(value);
        if (isEmpty())
        {
            frontNode = backNode = newNode;
        }
        else
        {
            backNode->next = newNode;
            backNode = newNode;
        }
    }

    T pop()
    {
        if (isEmpty())
        {
            throw std::runtime_error("Queue is empty");
        }
        Node* temp = frontNode;
        T data = temp->data;
        frontNode = frontNode->next;
        if (!frontNode)
        {
            backNode = nullptr;
        }
        delete temp;
        return data;
    }

    T& front() const
    {
        if (isEmpty())
        {
            throw std::runtime_error("Queue is empty");
        }
        return frontNode->data;
    }

    bool isEmpty() const
    {
        return frontNode == nullptr;
    }

    void displayQueue() const
    {
        if (isEmpty())
        {
            cout << "Queue is empty.\n";
            return;
        }

        Node* current = frontNode;
        //cout << "Queue contents: ";
        while (current != nullptr)
        {
            cout << endl;
            cout << current->data << " ";
            current = current->next;
        }
        cout << "\n";
    }


    CustomQueue& operator=(const CustomQueue& other)      //copy one queue to another
    {
        if (this == &other)
        {
            return *this;       //checking if the incoming queue is equal or not
        }

        // Clear current queue
        while (!isEmpty())
        {
            pop();
        }

        // Deep copy the other queue
        Node* current = other.frontNode;
        while (current)
        {
            push(current->data);
            current = current->next;
        }

        return *this;
    }
};

class Graph  // It uses a linked list of CityNode objects to represent cities, and each city can have a linked list of Flight objects to
    //represent the flights originating from that city. The Graph class also manages a list of booked flights.
{
private:
    CityNode* cities;                   //each city may have a list of flights that depart from it. The cities are stored in a linked list.
    BookedFlight* bookedFlights;       //BookedFlight objects represent flights that have been booked by the user. The flights are stored in a linked list.


public:
    Graph() : cities(NULL)
    {}


    ~Graph()
    {
        CityNode* tempCity = cities;         //starts by iterating over linkd list of ciies 
        while (tempCity)
        {
            Flight* tempFlight = tempCity->flights;         //iterates of linked list of lfights associated with that city 
            while (tempFlight)
            {
                Flight* nextFlight = tempFlight->next;
                delete tempFlight;              //deletes each flight object 
                tempFlight = nextFlight;
            }
            CityNode* nextCity = tempCity->next;
            delete tempCity;
            tempCity = nextCity;
        }

        BookedFlight* tempBooked = bookedFlights;   //now that link list are delted ,it will dlete vertices of graph
        while (tempBooked)
        {
            BookedFlight* nextBooked = tempBooked->next;
            delete tempBooked;
            tempBooked = nextBooked;
        }

    }

    int getCityIndex(string cityName) 
    {
        CityNode* temp = cities;
        int index = 0;

        while (temp) 
        {
            if (temp->cityName == cityName)    // If the current city's name matches the given name, return the index.
            {
                return index;
            }
            temp = temp->next;
            index++;
        }

        // Debugging output for missing city
        cout << "Error: City '" << cityName << "' not found.\n";
        return -1;
    }




    CityNode* getCityByIndex(int index) 
    {
        CityNode* current = cities;
        int currentIndex = 0;

        while (current) 
        {
            if (currentIndex == index)    // If the current index matches the input index, return the current node.
            {
                return current;
            }
            current = current->next;
            currentIndex++;
        }

        // Debugging output for invalid index
        cout << "Error: City at index " << index << " does not exist.\n";
        return nullptr;
    }


    string getCityName(int index)
    {
        CityNode* temp = cities;
        int currentIndex = 0;

        while (temp)
        {
            if (currentIndex == index)    // If the current index matches the input index, return the cityname.
            {
                return temp->cityName;
            }
            temp = temp->next;
            currentIndex++;
        }
        return " ";
    }

    void findShortestPath(string origin, string destination)   //using dijiktras theorem
    {
        const int INF = 999999;

        //Step1
        int numCities = 0;
        CityNode* tempCity = cities;
        while (tempCity)           
        {
            numCities++;
            tempCity = tempCity->next;
        }


        if (numCities == 0) 
        {
            cout << "No cities available in the graph.\n";
            return;
        }

        // Step 2: Initialize arrays dynamically
        int* dist = new int[numCities];
        bool* visited = new bool[numCities];
        int* prev = new int[numCities];

        for (int i = 0; i < numCities; i++) 
        {
            dist[i] = INF;
            visited[i] = false;
            prev[i] = -1;
        }

        // Step 3: Get indices for the origin and destination cities
        int originIndex = getCityIndex(origin);
        int destinationIndex = getCityIndex(destination);

        if (originIndex == -1 || destinationIndex == -1) 
        {
            cout << "Origin or destination city not found.\n";
            delete[] dist;
            delete[] visited;
            delete[] prev;
            return;
        }

        // Step 4: Set the starting city distance
        dist[originIndex] = 0;

        // Step 5: Implement Dijkstra's Algorithm
        for (int i = 0; i < numCities; i++) 
        {
            int u = -1;
            for (int j = 0; j < numCities; j++)
            {
                if (!visited[j] && (u == -1 || dist[j] < dist[u])) 
                {
                    u = j;
                }
            }

            if (u == -1 || dist[u] == INF) break;

            visited[u] = true;

            CityNode* currentCity = cities;
            for (int k = 0; k < u; k++) currentCity = currentCity->next;

            Flight* flight = currentCity->flights;
            while (flight) 
            {
                int neighborIndex = getCityIndex(flight->destination);
                if (!visited[neighborIndex]) 
                {
                    int weight = flight->price;
                    if (dist[u] + weight < dist[neighborIndex]) 
                    {
                        dist[neighborIndex] = dist[u] + weight;
                        prev[neighborIndex] = u;
                    }
                }
                flight = flight->next;
            }
        }

        // Step 6: Output the shortest path with layovers
        if (dist[destinationIndex] == INF)
        {
            cout << RED << "No path found from " << origin << " to " << destination << RESET << endl;
        }
        else 
        {
            cout << "Shortest path from " << origin << " to " << destination << endl;

            int* path = new int[numCities];
            int count = 0, current = destinationIndex;

            while (current != -1) 
            {
                path[count++] = current;
                current = prev[current];
            }

            for (int i = count - 1; i >= 0; i--) 
            {
                cout << getCityName(path[i]);
                if (i > 0) cout << " -> ";
            }

            cout << "\nTotal Cost: " << dist[destinationIndex] << RED << " units. " << RESET << endl;

            char choice;
            cout << "Do you want to book this shortest path? (y/n): ";
            cin >> choice;

            if (choice == 'y' || choice == 'Y') 
            {
                cout << "Booking the shortest path...\n";
                double totalCost = 0;
                for (int i = count - 1; i > 0; i--) {
                    CityNode* fromCity = getCityByIndex(path[i]);
                    CityNode* toCity = getCityByIndex(path[i - 1]);

                    if (!fromCity || !toCity)
                    {
                        cout << "Error: Invalid city node.\n";
                        return;
                    }

                    Flight* flight = fromCity->findFlightTo(toCity->cityName);
                    if (flight)
                    {
                        totalCost += flight->price;
                        cout << "Booked flight: " << fromCity->cityName << " -> " << toCity->cityName
                            << " | Cost: Rs " << flight->price << "\n";
                    }
                    else 
                    {
                        cout << "No flight found between " << fromCity->cityName << " and " << toCity->cityName << "\n";
                        return;
                    }
                }
                cout << "Total Cost: Rs " << totalCost << "\n";
                cout << BLUE << "\nTHANK YOU FOR BOOKING FLIGHT WITH SKYNAV HAVE A GREAT DAY" << RESET << endl;
            }
            else
            {
                cout << "No flight booked.\n";
            }

            delete[] path;
        }


        delete[] dist;
        delete[] visited;
        delete[] prev;
    }


    void findCheapestPath(string origin, string destination) 
    {
        const int INF = 999999;

        // Step 1: Count the total number of cities (numCities)
        int numCities = 0;
        CityNode* tempCity = cities;
        while (tempCity) 
        {
            numCities++;
            tempCity = tempCity->next;
        }


        if (numCities == 0) 
        {
            cout << "No cities available in the graph.\n";
            return;
        }

        // Step 2: Initialize arrays dynamically
        int* cost = new int[numCities];
        bool* visited = new bool[numCities];
        int* prev = new int[numCities];

        for (int i = 0; i < numCities; i++) 
        {
            cost[i] = INF;
            visited[i] = false;
            prev[i] = -1;
        }

        // Step 3: Get indices for the origin and destination cities
        int originIndex = getCityIndex(origin);
        int destinationIndex = getCityIndex(destination);

        if (originIndex == -1 || destinationIndex == -1) 
        {
            cout << "Origin or destination city not found.\n";
            delete[] cost;
            delete[] visited;
            delete[] prev;
            return;
        }

        // Step 4: Set the starting city cost
        cost[originIndex] = 0;

        // Step 5: Implement Dijkstra's Algorithm for Cheapest Path
        for (int i = 0; i < numCities; i++) 
        {

            int u = -1;
            for (int j = 0; j < numCities; j++) 
            {
                if (!visited[j] && (u == -1 || cost[j] < cost[u])) 
                {
                    u = j;
                }
            }

            if (u == -1 || cost[u] == INF) break;
            visited[u] = true;


            CityNode* currentCity = cities;
            for (int k = 0; k < u; k++) currentCity = currentCity->next;

            Flight* flight = currentCity->flights;
            while (flight) 
            {
                int neighborIndex = getCityIndex(flight->destination);
                if (!visited[neighborIndex]) 
                {
                    int weight = flight->price;
                    if (cost[u] + weight < cost[neighborIndex])
                    {
                        cost[neighborIndex] = cost[u] + weight;
                        prev[neighborIndex] = u;
                    }
                }
                flight = flight->next;
            }
        }


        if (cost[destinationIndex] == INF) 
        {
            cout << RED << "No path found from " << origin << " to " << destination << RESET << endl;
        }
        else {
            cout << "Cheapest path from " << origin << " to " << destination << ":\n";


            int* path = new int[numCities];
            int count = 0, current = destinationIndex;

            while (current != -1) 
            {
                path[count++] = current;
                current = prev[current];
            }

            for (int i = count - 1; i >= 0; i--) 
            {
                cout << getCityName(path[i]);
                if (i > 0) cout << " -> ";
            }

            cout << "\nTotal Cost: " << cost[destinationIndex] << " units\n";


            char choice;
            cout << "Do you want to book this cheapest path? (y/n): ";
            cin >> choice;

            if (choice == 'y' || choice == 'Y')
            {
                // Book the flights along the cheapest path
                cout << "Booking the cheapest path...\n";
                double totalCost = 0;
                for (int i = count - 1; i > 0; i--)
                {
                    CityNode* fromCity = getCityByIndex(path[i]);
                    CityNode* toCity = getCityByIndex(path[i - 1]);

                    if (!fromCity || !toCity) 
                    {
                        cout << "Error: Invalid city node.\n";
                        return;
                    }

                    Flight* flight = fromCity->findFlightTo(toCity->cityName);
                    if (flight) 
                    {
                        totalCost += flight->price;
                        cout << "Booked flight: " << fromCity->cityName << " -> " << toCity->cityName
                            << " | Cost: Rs " << flight->price << "\n";
                    }
                    else 
                    {
                        cout << "No flight found between " << fromCity->cityName << " and " << toCity->cityName << "\n";
                        return;
                    }
                }
                cout << "Total Cost: Rs " << totalCost << endl;
                cout << BLUE << "\nTHANK YOU FOR BOOKING FLIGHT WITH SKYNAV HAVE A GREAT DAY" << RESET << endl;
            }
            else 
            {
                cout << "No flight booked.\n";
            }

            delete[] path;
        }

        // Step 8: Free other dynamically allocated memory
        delete[] cost;
        delete[] visited;
        delete[] prev;
    }




    void addCity(string cityName, float charge = 0.0)   //adding cities 
    {
        CityNode* newCity = new CityNode(cityName, charge);
        newCity->next = cities;
        cities = newCity;
    }


    CityNode* findCity(string cityName)
    {
        CityNode* temp = cities;
        while (temp != NULL)
        {
            if (temp->cityName == cityName)        // If the current iname matches the input name, return the current node.
            {
                return temp;
            }
            temp = temp->next;
        }
        return NULL;
    }

    string trim(const string& str)       //removes leading and trailing whitespace 
    {
        int start = 0, end = str.length() - 1;
        // Move the start pointer forward to skip leading whitespace (spaces or tabs)
        while (start <= end && (str[start] == ' ' || str[start] == '\t'))          
        {
            start++;
        }
        // Move the end pointer backward to skip trailing whitespace (spaces or tabs)
        while (end >= start && (str[end] == ' ' || str[end] == '\t')) 
        {
            end--;
        }
        return str.substr(start, end - start + 1);
    }


    void findFlights(string origin, string destination, string date, Graph& graph)
    {

        origin = trim(origin);
        destination = trim(destination);
        date = trim(date);

        CityNode* originCity = findCity(origin);
        if (!originCity)
        {
            cout << "Origin city not found: " << origin << "\n";
            return;
        }
        else
        {
            Flight* temp = originCity->flights;
            bool found = false;
            int count = 1;
            cout << endl;
            while (temp)
            {

                //cout << "w3" << endl;
                if (temp->destination == destination && temp->date == date)   //when the desired flight is found
                {
                    cout << YELLOW << count << ". " << RESET << temp->airline << " from " << temp->origin << " to " << temp->destination << " on " << temp->date << endl;
                    cout << "Ticket price: " << temp->price << " Rupees.\n";
                    cout << "Departure Time: " << temp->departureTime << endl;
                    found = true;
                    count++;
                    //cout << "w3" << endl;
                    cout << endl;
                }
                temp = temp->next;
            }
            char choice1;
            if (found == true)      //if flight is found
            {

                cout << "Do you want to book a flight? (y/n) : ";
                cin >> choice1;

                if ((choice1 != 'y' && choice1 != 'Y') && (choice1 != 'n' && choice1 != 'N'))
                {
                    cout << "Invalid input." << endl;
                }
                else if (choice1 == 'y' || choice1 == 'Y')
                {

                    int choice;
                    cout << "Enter the number of your prefered flight: ";
                    cin >> choice;

                    if (choice < 1 || choice >= count)
                    {
                        cout << "INVALID CHOICE" << endl;
                    }

                    temp = originCity->flights;
                    count = 1;    //for numertain
                    while (temp != NULL)
                    {
                        if (temp->destination == destination && temp->date == date)
                        {
                            if (choice == count)
                            {
                                graph.bookFlight(origin, destination, date);
                                cout << "Fligth successfully booked" << endl;
                                cout << BLUE << "\nTHANK YOU FOR BOOKING FLIGHT WITH SKYNAV HAVE A GREAT DAY" << RESET << endl;
                                cout << endl;
                                //break;
                            }
                            count++;
                        }
                        temp = temp->next;

                    }

                }
                else if (choice1 == 'n' || choice1 == 'N')
                {
                    cout << "No flight booked." << endl;
                }
            }
            else if (!found)
            {
                cout << "No flights found for the given details" << endl;
            }
        }

    }

    void parseHotelCharges(const string& filename)       //parsing by using the given txt file
    {
        ifstream file(filename);
        if (!file.is_open()) 
        {
            cout << "Error opening file: " << filename << "\n";
            return;
        }

        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string cityName;
            float charge;

            ss >> cityName >> charge;

            CityNode* city = findCity(cityName);
            if (city)
            {
                city->hotelCharge = charge;
                //addCity(cityName, charge);
            }
            else
            {
                addCity(cityName, charge);
            }
        }
        file.close();
    }

    void bookHotel(const string& city, CustomQueue<CityNode*>& hotelbookings)     //book hotel in the city if stay is longer
    {
        char choice;
        cout << endl;
        cout << "Do you want to book a hotel in " << city << " :(y/n)";
        cin >> choice;
        if ((choice != 'y' && choice != 'Y') && (choice != 'n' && choice != 'N'))
        {
            cout << endl;
            cout << "Invalid input." << endl;
        }

        else if (choice == 'y' || choice == 'Y')
        {
            CityNode* temp = cities;
            while (temp != NULL)
            {
                if (temp->cityName == city)
                {
                    hotelbookings.push(temp); //keeping track of all hotels booked
                    cout << CYAN << "Hotel booked successfully in " << temp->cityName << RESET << endl;
                    cout << endl;
                    return;
                }
                temp = temp->next;
            }
            cout << "City not found for hotel booking.\n";
        }
        else if (choice == 'n' || choice == 'N')
        {
            cout << endl;
            cout << "No hotel booked." << endl;
            cout << endl;
            return;
        }
    }


    void bookFlight(string origin, string destination, string date)      //book flight of desired origina nd destination
    {
        CityNode* originCity = findCity(origin);
        if (!originCity)
        {
            cout << "Origin city not found.\n";
            return;
        }

        Flight* temp = originCity->flights;
        Flight* prev = nullptr;

        while (temp) 
        {
            if (temp->destination == destination && temp->date == date)
            {
                cout << endl;
                cout << RED << "Booking flight..." << RESET << endl;         //processing
                if (prev)
                {
                    prev->next = temp->next;
                }
                else
                {
                    originCity->flights = temp->next;
                }


                BookedFlight* newBookedFlight = new BookedFlight(temp);        //keeping track of booked flights
                newBookedFlight->next = bookedFlights;
                bookedFlights = newBookedFlight;

                displayBookedFlights();

                return;
            }
            prev = temp;
            temp = temp->next;
        }

        cout << "Flight not found.\n";
    }

     
    void displayBookedFlights()     //displaying all booked fligths
    {
        if (bookedFlights == nullptr)
        {
            cout << "No flights booked yet.\n";
            return;
        }

        BookedFlight* temp = bookedFlights;
        while (temp)
        {
            cout << endl;
            cout << "Booked Flight: " << temp->flight->airline << " from " << temp->flight->origin
                << " to " << temp->flight->destination << " on " << temp->flight->date << "\n";
            cout << "Ticket price: " << temp->flight->price << " Rupees.\n";
            cout << endl;
            temp = temp->next;
        }
    }


    void addFlight(string origin, string destination, string airline, string date, string depTime, string arrTime, float price, string dur)
    {    //add flight details in the graph

        CityNode* originCity = findCity(origin);
        // If the origin city does not exist, add it to the graph
        if (originCity == NULL)
        {
            addCity(origin);
            originCity = findCity(origin);         // Retrieve the newly added city
        }
        CityNode* destinationCity = findCity(destination);
        // If the destination city does not exist, add it to the graph
        if (destinationCity == NULL) 
        {
            addCity(destination);
        }


        Flight* newFlight = new Flight(origin, destination, airline, date, depTime, arrTime, price, dur);
        originCity->addFlight(newFlight);
    }

    string formatDate(string date)  //chnaging th format in how date in stored in txt file
    {
        stringstream ss(date);
        string day, month, year;
        getline(ss, day, '/');
        getline(ss, month, '/');
        getline(ss, year);

        // Add a leading zero to single-digit days for consistency
        if (day.length() == 1)
        {
            day = "0" + day;
        }

        // Add a leading zero to single-digit months for consistency
        if (month.length() == 1)
        {
            month = "0" + month;
        }

        // Return the formatted date in "DD-MM-YYYY" format
        return day + "-" + month + "-" + year;
    }

    void parseFlights(const string& filename)     //parsing flights from the given ttxt file
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cout << "Error opening file: " << filename << "\n";
            return;
        }

        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string origin, destination, airline, date, depTime, arrTime, dur;
            float price;

            ss >> origin >> destination >> date >> depTime >> arrTime >> price >> airline;
            date = formatDate(date);

            addFlight(origin, destination, airline, date, depTime, arrTime, price, dur);
        }
        file.close();
    }


    void displayAllFlights()   //displaying all flights
    {
        if (cities == NULL) 
        {
            cout << "No cities in the graph.\n";
            return;
        }

        CityNode* tempCity = cities;
        while (tempCity != NULL)
        {
            cout << "FLIGHTS AVAILABLE FROM :  " << tempCity->cityName << endl;

            if (tempCity->flights == NULL) {
                cout << " NO FLIGHTS ARE AVAILABLE FROM : " << tempCity->cityName << endl;

            }
            else {
                Flight* tempFlight = tempCity->flights;
                while (tempFlight != NULL)
                {
                    cout << endl;
                    cout << "  Flight: " << tempFlight->airline << " from " << tempFlight->origin
                        << " to " << tempFlight->destination << " on " << tempFlight->date << "\n";
                    cout << "    Departure: " << tempFlight->departureTime << "\n";
                    cout << "    Arrival: " << tempFlight->arrivalTime << "\n";
                    cout << "    Price: " << tempFlight->price << " Rupees.\n";
                    tempFlight = tempFlight->next;
                    cout << endl;
                }
            }
            cout << "------------------------------------------------------------\n";
            tempCity = tempCity->next;
        }
    }

    void DFS(string origin)   //depth first traversal
    {

        CityNode* start = findCity(origin);
        if (!start)
        {
            cout << "Origin city not found: " << origin << "\n";
            return;
        }

        Stack stack;
        VisitedList visited;

        stack.push(start);         //psuhing the origin city

        while (!stack.isEmpty())
        {
            CityNode* currentCity = stack.pop();


            if (visited.isVisited(currentCity->cityName))   //checks if its already visited
            {
                continue;
            }



            visited.addVisited(currentCity->cityName);
            cout << "Visiting city: " << currentCity->cityName << "\n";

            // Push all connected cities (neighbors) onto the stack
            Flight* flight = currentCity->flights;
            while (flight)
            {

                CityNode* neighborCity = findCity(flight->destination);
                //cout << neighborCity->cityName << endl;
                
                 // If the neighbor city is valid and not yet visited, push it onto the stack
                if (neighborCity && !visited.isVisited(neighborCity->cityName))
                {
                    stack.push(neighborCity);
                }
                flight = flight->next;
            }
        }
    }
};

template <typename T>  //using templates so that the class can operate on any data type, making the code more reusable and flexible
class CustomStack 
{
private:
    struct Node    //priv node class to sue in this stack
    {
        T data;
        Node* next;
        Node(const T& value, Node* nextNode = nullptr) : data(value), next(nextNode) {}
    };
    Node* topNode;

public:
    CustomStack() : topNode(nullptr) 
    {}

    ~CustomStack() 
    {
        while (!isEmpty()) 
        {
            pop();
        }
    }

    void push(const T& value)
    {
        topNode = new Node(value, topNode);
    }

    T pop() 
    {
        if (isEmpty())
        {
            throw runtime_error("Stack is empty");
        }
        Node* temp = topNode;
        T data = temp->data;
        topNode = topNode->next;
        delete temp;
        return data;
    }

    T& top() const 
    {
        if (isEmpty()) 
        {
            throw runtime_error("Stack is empty");
        }
        return topNode->data;
    }

    bool isEmpty() const 
    {
        return topNode == nullptr;
    }
};



class LayoverQueue
{
private:
    struct PathNode      //priv node to use in in this queue
    {
        Flight* flight;
        PathNode* next;
    };

    PathNode* front;
    PathNode* rear;

public:
    LayoverQueue() : front(nullptr), rear(nullptr)
    {
    }

    void enqueue(PathNode* newNode)
    {
        if (rear == nullptr)
        {

            front = rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }
    }

    PathNode* dequeue()
    {
        if (front == nullptr)
        {
            return nullptr;
        }
        PathNode* temp = front;
        front = front->next;
        if (front == nullptr)
        {
            rear = nullptr;
        }
        return temp;
    }

    bool isEmpty()
    {
        return front == nullptr;
    }

    void displayQueue()     
    {
        PathNode* current = front;
        while (current != nullptr)
        {
            Flight* flight = current->flight;
            cout << endl;
            cout << "Flight: " << flight->airline << " from " << flight->origin
                << " to " << flight->destination << " on " << flight->date << "\n";
            cout << "    Departure: " << flight->departureTime << "\n";
            cout << "    Arrival: " << flight->arrivalTime << "\n";
            cout << endl;
            current = current->next;
        }
    }

    void clear()
    {
        while (!isEmpty())
        {
            PathNode* temp = dequeue();
            delete temp;
        }
    }

    int timeToMinutes(string time)    //converting time to minutes for easy use and understanding and calculations of layover time 
    {
        // If the time has only a single digit for the hour, prepend a '0' for proper formatting
        if (time[1] == ':')
        {
            time = "0" + time;
        }
        // Validate time format: "HH:MM"
        if (time.length() != 5 || time[2] != ':')
        {
            cout << "Error: Invalid time format: " << time << "\n";
            return -1;  // Invalid format
        }

        string hoursStr = time.substr(0, 2);
        string minutesStr = time.substr(3, 2);

        // Ensure both hours and minutes are numeric
        if (!isdigit(hoursStr[0]) || !isdigit(hoursStr[1]) || !isdigit(minutesStr[0]) || !isdigit(minutesStr[1])) {
            cout << "Error: Invalid time format: " << time << "\n";
            return -1;  // Invalid time format
        }

        int hours = stoi(hoursStr);
        int minutes = stoi(minutesStr);

        // Validate hour and minute ranges
        if (hours < 0 || hours >= 24 || minutes < 0 || minutes >= 60) {
            cout << "Error: Invalid time range: " << time << "\n";
            return -1;  // Invalid range
        }

        //cout << "hrs : " << hours;
        //cout << "mins : " << minutes;
        return hours * 60 + minutes;  // Convert to minutes
    }

    // Helper function to compare two dates (format: "DD/MM/YYYY")
    bool isValidDate(const string& prevDate, const string& currDate)
    {
        //cout << "Comparing Dates - Previous Date: " << prevDate << ", Current Date: " << currDate << endl;

        // Extract day, month, year from both dates
        int prevDay = stoi(prevDate.substr(0, 2));
        int prevMonth = stoi(prevDate.substr(3, 2));
        int prevYear = stoi(prevDate.substr(6, 4));

        int currDay = stoi(currDate.substr(0, 2));
        int currMonth = stoi(currDate.substr(3, 2));
        int currYear = stoi(currDate.substr(6, 4));

        // Compare years first
        if (currYear > prevYear)
        {

            return true; // If the current year is greater, it's valid
        }
        else if (currYear < prevYear)
        {

            return false; // Invalid if the current year is earlier
        }

        // If the years are the same, compare months
        if (currMonth > prevMonth)
        {

            return true;
        }
        else if (currMonth < prevMonth)
        {

            return false;
        }

        // If the months are the same, compare days
        if (currDay >= prevDay)
        {

            return true;
        }

        cout << "Current day is earlier than previous day.\n";
        return false;
    }

    bool isValidLayover(const string& prevArrivalTime, const string& prevFlightDate, const string& currDepartureTime, const string& currFlightDate)
    {
        // Check if the flight dates are valid by checking if the current flight date should be >= the previous flight date)
        //converting time
        int prevArrivalMinutes = timeToMinutes(prevArrivalTime);
        int currDepartureMinutes = timeToMinutes(currDepartureTime);

        if (prevArrivalMinutes > currDepartureMinutes)
        {
            if (!isValidDate(prevFlightDate, currFlightDate))
            {
                return false;
            }
        }
        //cout << endl;
        //cout << "Valid Layover." << endl;
        return true;
    }

    void findFlightsWithLayovers(string origin, string destination, string date, Graph& graph)
    {

        CustomQueue<CustomQueue<CityNode*>> layoverPaths = DFSForLayovers(origin, destination, graph);

        if (layoverPaths.isEmpty())
        {
            cout << "No possible layovers found.\n";
            return;
        }

        CustomQueue<CustomQueue<CityNode*>> validPaths;             //creating a queue storng queues of citynode
        CustomQueue<CustomQueue<CityNode*>> tempPaths = layoverPaths;      // Copy of the layover paths for processing

        cout << endl;
        cout << "Processing layover paths..." << endl;       //preocessing


        while (!tempPaths.isEmpty())      //checking each path to see if its valif odr not
        {
            CustomQueue<CityNode*> path = tempPaths.front();
            tempPaths.pop();

            bool isValid = true;
            string prevArrivalTime = "00:00";       // Default arrival time for the first flight
            string prevFlightDate = date;
            CityNode* prevCity = nullptr;

            cout << endl;
            cout << "Processing path: ";
            displayLayovers(path);


            CustomQueue<CityNode*> pathCopy = path;         // Copy the path to store in validPaths if it's valid
            while (!path.isEmpty())
            {
                CityNode* currCity = path.front();
                path.pop();

                if (prevCity)
                {
                    // Find the connecting flight
                    Flight* connectingFlight = prevCity->findFlightTo(currCity->cityName);
                    if (!connectingFlight)
                    {
                        cout << endl;
                        cout << "No connecting flight found between " << prevCity->cityName
                            << " and " << currCity->cityName << endl;
                        cout << endl;
                        isValid = false;
                        break;
                    }
                    if (!isValidLayover(prevArrivalTime, prevFlightDate, connectingFlight->departureTime, connectingFlight->date))
                    {
                        //cout << endl;
                        //cout << "Invalid Layover." << endl;
                        isValid = false;
                        break;
                    }

                    // Update for the next leg of the path
                    prevArrivalTime = connectingFlight->arrivalTime;
                    prevFlightDate = connectingFlight->date;
                }
                else
                {
                    prevArrivalTime = "00:00"; // Default time for the first flight
                    prevFlightDate = date;    // Use the provided date
                }

                prevCity = currCity;
            }

            if (isValid)
            {
                cout << "Path is valid. Adding to valid paths.\n";
                validPaths.push(pathCopy); // Use the copy to preserve the original path
            }
            else
            {
                cout << RED << "Path is invalid." << RESET << endl;
                cout << endl;
            }
        }

        if (validPaths.isEmpty())
        {
            cout << endl;
            cout << "No valid layover paths found.\n";
            return;
        }

        cout << "Valid Flights with Layovers:" << endl;
        cout << endl;

        CustomQueue<CustomQueue<CityNode*>> tempValidPaths = validPaths;
        int count = 1;  //numerating and counting 

        while (!tempValidPaths.isEmpty())
        {
            CustomQueue<CityNode*> validPath = tempValidPaths.front();
            tempValidPaths.pop();
            cout << count << ". ";
            count++;
            displayLayovers(validPath);
        }
        cout << endl;
        char choice1;
        cout << "Do you want to book a flight? (y/n) : ";
        cin >> choice1;

        if ((choice1 != 'y' && choice1 != 'Y') && (choice1 != 'n' && choice1 != 'N'))
        {
            cout << endl;
            cout << "Invalid input." << endl;
        }

        else if (choice1 == 'y' || choice1 == 'Y')
        {
            bookLayoverFlights(validPaths, graph);
            // cout << "check" << endl;
        }

        else if (choice1 == 'n' || choice1 == 'N')
        {
            cout << endl;
            cout << "No flight booked." << endl;
        }
    }
    void bookLayoverFlights(CustomQueue<CustomQueue<CityNode*>>& validPaths, Graph& g)    //booking the valid layover path 
    {
        if (validPaths.isEmpty())
        {
            cout << endl;
            cout << "No valid layover paths to book.\n";
            return;
        }

        CustomQueue<CustomQueue<Flight*>> bookedFlights;
        cout << endl;
        cout << "Available Valid Layover Paths:\n";
        CustomQueue<CustomQueue<CityNode*>> tempPaths = validPaths;
        int pathIndex = 1;

        cout << endl;
        while (!tempPaths.isEmpty())   //listing all the valid paths
        {
            CustomQueue<CityNode*> path = tempPaths.front();
            tempPaths.pop();
            cout << "Path " << pathIndex << ": ";
            displayLayovers(path);
            pathIndex++;
        }
        cout << endl;
        //taking user preference
        cout << "Enter the layover number you want to book (or 0 to cancel): ";
        int choice;
        cin >> choice;
        cout << endl;

        // Check for invalid choice input
        if (choice <= 0 || choice >= pathIndex)
        {
            cout << endl;
            cout << "Invalid choice (" << choice << "). Booking cancelled.\n";
            cout << "Booking cancelled.\n";
            cout << endl;
            return;
        }

        tempPaths = validPaths; // Reset tempPaths
        CustomQueue<CityNode*> chosenPath;
        CustomQueue<CityNode*> hotelBookings;

        for (int i = 1; i <= choice; ++i)
        {
            CustomQueue<CityNode*> currentPath = tempPaths.front();
            tempPaths.pop();

            if (i == choice)
            {
                // Perform a deep copy of the selected path to `chosenPath`
                while (!currentPath.isEmpty())
                {
                    CityNode* node = currentPath.front();
                    if (node == nullptr)
                    {
                        cout << "Error" << endl;
                        return;
                    }
                    chosenPath.push(node);
                    currentPath.pop();
                }
                break;
            }
        }

        if (chosenPath.isEmpty())
        {
            cout << "Error" << endl;
            return;
        }

        // Convert chosen path to flight details
        CustomQueue<Flight*> flightDetails;
        CityNode* prevCity = nullptr;
        bool layoverChecked = false;  // Flag to check when we encounter a layover city
        string arrivalTime = "";
        string departureTime = "";

        while (!chosenPath.isEmpty())
        {
            CityNode* currCity = chosenPath.front();
            chosenPath.pop();

            if (currCity == nullptr) 
            {
                cout << "Error" << endl;
                return;
            }

            if (prevCity) 
            {
                Flight* connectingFlight = prevCity->findFlightTo(currCity->cityName);

                if (connectingFlight)
                {
                    flightDetails.push(connectingFlight);
                    cout << "Booked flight: " << prevCity->cityName << " -> " << currCity->cityName << "\n";


                    if (!layoverChecked)     //if layover not cheked then it saves the arrival time to calculate the stau in the city 
                    {
                        arrivalTime = connectingFlight->arrivalTime;
                        cout << "Arrival time in " << currCity->cityName << ": " << arrivalTime << "\n";
                        cout << endl;
                    }


                    departureTime = connectingFlight->departureTime;      //storing deaprture time from that city to next
                    cout << "Departure time from " << currCity->cityName << " to next destination: " << departureTime << "\n";
                    cout << endl;


                    if (arrivalTime != "" && departureTime != "") //not empty/niull
                    {
                        int layoverDuration = calculateTimeDifference(arrivalTime, departureTime);    //calculating differece to see the total transit

                        cout << "Layover Duration in " << currCity->cityName << ": " << layoverDuration << " minutes\n";
                        cout << endl;


                        if (layoverDuration < 720)
                        { // 12 hours = 720 minutes
                            cout << "Layover is too short in " << currCity->cityName << ".\n";
                        }
                        else
                        {
                            cout << endl;
                            cout << "Layover is long enough, you can book a hotel in " << CYAN << currCity->cityName << RESET << endl;
                            g.bookHotel(currCity->cityName, hotelBookings);
                        }
                    }

                    layoverChecked = true;
                }
                else {
                    cout << "No connecting flight found between " << prevCity->cityName << " and " << currCity->cityName << "\n";
                }
            }
            prevCity = currCity;
        }

        // Check if any flights were booked
        if (flightDetails.isEmpty())
        {
            cout << "No flights found for the chosen path.\n";
            return;
        }

        // Add to booked flights
        bookedFlights.push(flightDetails);
        cout << "Flight successfully booked!" << endl;
        // Calculate and display the total price
        double totalPrice = calculateTotalPrice(flightDetails);
        cout << "Total Price: Rs " << totalPrice << endl;

        // Display all hotel bookings if any
        if (!hotelBookings.isEmpty())
        {
            cout << "\nBooked Hotels:\n";
            while (!hotelBookings.isEmpty())
            {
                CityNode* hotelCity = hotelBookings.front();
                hotelBookings.pop();
                cout << "Hotel booked in " << hotelCity->cityName << endl;
            }
        }

        cout << BLUE << "\nTHANK YOU FOR BOOKING FLIGHT WITH SKYNAV HAVE A GREAT DAY" << RESET << endl;

        cout << endl << endl;
    }

    int calculateTimeDifference(string arrivalTime, string departureTime)
    {

        int arrivallMin = timeToMinutes(arrivalTime);
        int departureMin = timeToMinutes(departureTime);

        // If the departure is the next day, add 1440 minutes (24 hours)
        if (departureMin < arrivallMin)
        {
            departureMin += 1440;     //to avoid negetive numbrs
        }

        return departureMin - arrivallMin;
    }





    double calculateTotalPrice(CustomQueue<Flight*> flights)
    {
        double totalPrice = 0;
        CustomQueue<Flight*> tempQueue = flights; // Copy to avoid modifying the original queue

        while (!tempQueue.isEmpty())
        {
            Flight* flight = tempQueue.front();
            tempQueue.pop();
            totalPrice += flight->price;
        }

        return totalPrice;
    }

    bool isPathDuplicate(const CustomQueue<CityNode*>& newPath, CustomQueue<CustomQueue<CityNode*>>& allPaths)
    { //cheing if the path is already oushed in the queue
        CustomQueue<CustomQueue<CityNode*>> tempPaths = allPaths;

        while (!tempPaths.isEmpty())
        {
            CustomQueue<CityNode*> existingPath = tempPaths.front();
            tempPaths.pop();

            CustomQueue<CityNode*> temp1 = newPath;
            CustomQueue<CityNode*> temp2 = existingPath;

            // Compare both paths element by element
            while (!temp1.isEmpty() && !temp2.isEmpty())
            {
                if (temp1.front() != temp2.front())
                {
                    break;
                }
                temp1.pop();
                temp2.pop();
            }

            // If both are empty, paths are equal
            if (temp1.isEmpty() && temp2.isEmpty())
            {
                return true;
            }
        }

        return false;
    }


    CustomQueue<CustomQueue<CityNode*>> DFSForLayovers(string originCity, string destination, Graph& g)  //deapth first traversal
    {
        CustomQueue<CustomQueue<CityNode*>> allPaths;       // Queue to store all the valid paths from origin to destination
        CityNode* start = g.findCity(originCity);    

        if (!start)
        {
            cout << "ORIGIN CITY NOT FOUND: " << originCity << endl;
            return allPaths;
        }

        Stack stack1;         // Stack for DFS traversal
        CustomStack<CustomQueue<CityNode*>> pathStack;       // Stack to store paths
        VisitedList visited;   

        stack1.push(start);
        CustomQueue<CityNode*> currPath;      //path that will eb followed
        currPath.push(start);
        pathStack.push(currPath);

        while (!stack1.isEmpty())
        {
            CityNode* currentCity = stack1.pop();
            CustomQueue<CityNode*> pathToCurrentCity = pathStack.top();
            pathStack.pop();

            // If the destination city is reached, check if the path is already found
            if (currentCity->cityName == destination)
            {
                if (!isPathDuplicate(pathToCurrentCity, allPaths))
                {
                    allPaths.push(pathToCurrentCity);
                    displayLayovers(pathToCurrentCity);
                }
                continue;
            }

            // If the city has already been visited, skip it
            if (visited.isVisited(currentCity->cityName))
            {
                continue;
            }
            visited.addVisited(currentCity->cityName);

            Flight* flight = currentCity->flights;
            while (flight)
            {
                CustomQueue<CityNode*> newPath = pathToCurrentCity;
                CityNode* neighborCity = g.findCity(flight->destination);

                // If the neighbor city exists and is not visited, push it onto the stack
                if (neighborCity && !visited.isVisited(neighborCity->cityName)) 
                {
                    newPath.push(neighborCity);
                    pathStack.push(newPath);
                    stack1.push(neighborCity);
                }
                flight = flight->next;
            }
        }
        return allPaths;
    }


    void displayLayovers(CustomQueue<CityNode*> q)
    {
        if (q.isEmpty())
        {
            cout << "NO LAYOVERS EXITS " << endl;
            return;
        }
        CityNode* current = q.front();
        cout << "POSSIBLE LAYOVERS THAT EXIST : ";
        while (!q.isEmpty())
        {
            current = q.front();
            q.pop();


            cout << current->cityName << "(" << current->flights->airline << "," << current->flights->departureTime << ")";
            if (!q.isEmpty())
            {
                cout << " -> ";  // Print the arrow if it's not the last city
            }
        }
        cout << endl;
    }



};
//graphics
struct City1 {
    std::string name;
    float x, y;  // Position of the city (x, y coordinates)
};

// Define the Flight structure
struct Flight1 {
    City1* origin;      // Pointer to the origin city
    City1* destination; // Pointer to the destination city
    bool isDirect;      // True if direct flight, false for layover
};

// Constants for the number of cities and flights
const int MAX_CITIES = 11;
const int MAX_FLIGHTS = 30;

// Array of cities (example)
City1 cities[MAX_CITIES] = {
    {"New York", 100, 100},
    {"Paris", 500, 100},
    {"Tokyo", 300, 300},
    {"London", 700, 200},
    {"Islamabad", 200, 400},
    {"Berlin", 600, 500},
    {"Singapore", 150, 600},
    {"Seoul", 450, 600},
    {"Sydney", 800, 650},
    {"Amsterdam", 550, 200},
    {"Hong Kong", 350, 500}
};

// Array of flights (example)
Flight1 flights[MAX_FLIGHTS] = {
    {&cities[0], &cities[1], true},  // Direct flight from New York to Paris
    {&cities[1], &cities[2], false}, // Layover flight from Paris to Tokyo
    {&cities[0], &cities[3], true},  // Direct flight from New York to London
    {&cities[0], &cities[4], true},  // Direct flight from New York to Islamabad
    {&cities[1], &cities[4], true},  // Direct flight from Paris to Islamabad
    {&cities[4], &cities[5], true},  // Direct flight from Islamabad to Berlin
    {&cities[5], &cities[6], false}, // Layover flight from Berlin to Singapore
    {&cities[6], &cities[7], true},  // Direct flight from Singapore to Seoul
    {&cities[7], &cities[8], false}, // Layover flight from Seoul to Sydney
    {&cities[8], &cities[9], true},  // Direct flight from Sydney to Amsterdam
    {&cities[9], &cities[10], true}, // Direct flight from Amsterdam to Hong Kong
    {&cities[2], &cities[9], false}, // Layover flight from Tokyo to Amsterdam
    {&cities[1], &cities[7], false}, // Layover flight from Paris to Seoul
    {&cities[3], &cities[6], true},  // Direct flight from London to Singapore
    {&cities[0], &cities[10], false}, // Layover flight from New York to Hong Kong
    {&cities[10], &cities[5], true}, // Direct flight from Hong Kong to Berlin
    {&cities[3], &cities[0], true},  // Direct flight from London to New York
    {&cities[2], &cities[5], false}, // Layover flight from Tokyo to Berlin
    {&cities[9], &cities[8], true},  // Direct flight from Amsterdam to Sydney
    {&cities[7], &cities[0], false}, // Layover flight from Seoul to New York
    {&cities[4], &cities[3], true},  // Direct flight from Islamabad to London
    {&cities[5], &cities[7], false}, // Layover flight from Berlin to Seoul
    {&cities[6], &cities[2], true},  // Direct flight from Singapore to Tokyo
    {&cities[1], &cities[0], true},  // Direct flight from Paris to New York
    {&cities[7], &cities[6], false}, // Layover flight from Seoul to Singapore
    {&cities[9], &cities[2], true},  // Direct flight from Amsterdam to Tokyo
    {&cities[10], &cities[4], false}, // Layover flight from Hong Kong to Islamabad
    {&cities[0], &cities[8], true},  // Direct flight from New York to Sydney
    {&cities[3], &cities[10], false}, // Layover flight from London to Hong Kong
    {&cities[6], &cities[1], false}  // Layover flight from Singapore to Paris
};

void drawDashedLine(sf::RenderWindow& window, sf::Vector2f start, sf::Vector2f end) {
    const float dashLength = 5.0f;  // Length of each dash
    sf::Vector2f direction = end - start;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    direction /= length;  // Normalize the direction vector

    // Draw dashed segments
    for (float i = 0; i < length; i += dashLength * 2) {
        sf::Vertex dashStart = sf::Vertex(start + direction * i, sf::Color::Blue);
        sf::Vertex dashEnd = sf::Vertex(start + direction * (i + dashLength), sf::Color::Blue);

        // Create an array of 2 vertices to represent a single dash
        sf::Vertex dash[] = { dashStart, dashEnd };

        // Draw the dash (line segment)
        window.draw(dash, 2, sf::Lines);
    }
}

const int MAX_CONNECTIONS = 100;  // Choose a reasonable maximum
Flight1 allConnections[MAX_CONNECTIONS];
int connectionCount = 0; // Tracks the number of connections

void dfs(int currentCityIndex, int startCityIndex, City1 cities[], int numCities, Flight1 allConnections[], int& connectionCount, Flight1 flights[], int numFlights, bool visited[]) {
    visited[currentCityIndex] = true;

    for (int i = 0; i < numFlights; ++i) {
        if (flights[i].origin == &cities[currentCityIndex]) {
            int nextCityIndex = -1;

            // Find the index of the destination city
            for (int j = 0; j < numCities; ++j) {
                if (&cities[j] == flights[i].destination) {
                    nextCityIndex = j;
                    break;
                }
            }

            // If the city is valid and not yet visited
            if (nextCityIndex != -1 && !visited[nextCityIndex]) {
                // Add this connection if there's room
                if (connectionCount < MAX_CONNECTIONS) {
                    allConnections[connectionCount++] = { flights[i].origin, flights[i].destination, flights[i].isDirect };
                }

                // Recurse to the next city
                dfs(nextCityIndex, startCityIndex, cities, numCities, allConnections, connectionCount, flights, numFlights, visited);
            }
        }
    }

    visited[currentCityIndex] = false;  // Backtrack
}

void findAllConnections(City1 cities[], int numCities, Flight1 allConnections[], int& connectionCount, Flight1 flights[], int numFlights) {
    // Use a visited array to avoid revisiting cities
    bool visited[MAX_CITIES] = { false };

    // Run DFS for all cities as start points
    for (int i = 0; i < numCities; ++i) {
        dfs(i, i, cities, numCities, allConnections, connectionCount, flights, numFlights, visited);
    }
}







void drawCitiesAndFlights(sf::RenderWindow& window, City1 cities[], int numCities, Flight1 flights[], int numFlights) {
    // Step 1: Draw cities as circles
    for (int i = 0; i < numCities; ++i) {
        sf::CircleShape cityCircle(20);  // Radius of 20
        cityCircle.setFillColor(sf::Color::Green);  // Color the circle green
        cityCircle.setPosition(cities[i].x - 20, cities[i].y - 20);  // Position the circle at the city's coordinates
        window.draw(cityCircle);

        // Draw city name (optional, for debugging)
        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {  // Make sure you have a font file
            std::cout << "Error loading font." << std::endl;
        }

        sf::Text cityName(cities[i].name, font, 15);
        cityName.setFillColor(sf::Color::Black);  // Color the text black
        cityName.setPosition(cities[i].x - 10, cities[i].y - 10);  // Position the text close to the city
        window.draw(cityName);
    }

    // Step 2: Draw flights as lines between cities
    for (int i = 0; i < numFlights; ++i) {
        if (flights[i].isDirect) {
            // Draw a solid red line for direct flights
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(flights[i].origin->x, flights[i].origin->y)),
                sf::Vertex(sf::Vector2f(flights[i].destination->x, flights[i].destination->y))
            };
            line[0].color = sf::Color::Red;
            line[1].color = sf::Color::Red;
            window.draw(line, 2, sf::Lines);  // Draw the line
        }
        else {
            // Draw a dashed blue line for layover flights
            drawDashedLine(window, sf::Vector2f(flights[i].origin->x, flights[i].origin->y), sf::Vector2f(flights[i].destination->x, flights[i].destination->y));
        }
    }
}



int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Flight Path Visualizer");

    cout << BLUE << "****************************************************************************************************************************************" << endl;
    cout << "**                                                                                                                                    **" << endl;
    cout << "**              ***     ***     ***   ***        ***       ***         ***            ***           ***                    ***        ** " << endl;
    cout << "**             *****    ***    ***    ***        ***       ****        ***          *** ***          ***                  ***         ** " << endl;
    cout << "**            ******    ***   ***      ***      ***        *****       ***         ***   ***          ***                ***          ** " << endl;
    cout << "**            **        ***  ***          ******           *** ***     ***        ***     ***          ***              ***           ** " << endl;
    cout << "**             ***      *** ***             ***            ***  ***    ***       ***       ***          ***            ***            ** " << endl;
    cout << "**              ****    ******              ***            ***   ***   ***      ***************          ***          ***             ** " << endl;
    cout << "**               ****   ******              ***            ***    ***  ***     *****************          ***        ***              ** " << endl;
    cout << "**                 **   *** ***             ***            ***     *** ***    ***             ***          ***      ***               ** " << endl;
    cout << "**             ******   ***  ***            ***            ***       *****   ***               ***          ***    ***                ** " << endl;
    cout << "**              *****   ***   ***           ***            ***        ****  ***                 ***          ***  ***                 ** " << endl;
    cout << "**               ***    ***    ***          ***            ***         *** ***                   ***          *******                 ** " << endl;
    cout << "**                                                                                                                                    **" << endl;
    cout << "****************************************************************************************************************************************" << RESET << endl;

    cout << endl << endl;

    int choice;
    cout << "--------------- Welcome to SkyNav AI --------------\n";

    Graph g;

    LayoverQueue layoverQueue;
    g.parseFlights("Flights.txt");
    g.parseHotelCharges("HotelCharges_perday.txt");

    bool running = true;
    while (window.isOpen() && running)
    {
        // Handle SFML window events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close(); // Close the window when the "close" event is triggered
        }

        // Clear the window and set background color
        window.clear(sf::Color::White);

        // Draw cities and flights (Your function to render graphical elements)
        drawCitiesAndFlights(window, cities, MAX_CITIES, flights, MAX_FLIGHTS);

        // Display everything on the window
        window.display();

        // Process terminal input after rendering the window
        cout << "1. View Available Flights\n";
        cout << "2. Search Flights\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            g.displayAllFlights();
            break;
        }
        case 2:
        {
            int choice2;
            cout << "Enter which flight you would like to take : " << endl;
            cout << "1. Direct flight" << endl;
            cout << "2. Flight with Layovers " << endl;
            cin >> choice2;
            if (choice2 == 1)
            {
                string origin, destination, date;
                cout << "Enter origin : ";
                cin >> origin;
                cout << "Enter Destination : ";
                cin >> destination;
                cout << "Enter Date(DD - MM - YYYY) : ";
                cin >> date;
                g.findFlights(origin, destination, date, g);
            }
            else if (choice2 == 2)
            {
                string origin, destination, date;
                cout << "Enter origin : ";
                cin >> origin;
                cout << "Enter Destination : ";
                cin >> destination;
                cout << "Enter Date(DD - MM - YYYY) : ";
                cin >> date;
                int option;
                cout << "Choose how you'd like to search for flights:" << endl;
                cout << "1. View available flights with layovers . " << endl;
                cout << "2. Find the shortest Path (Best route)" << endl;
                cout << "3. Find the Cheapest Path " << endl;
                cin >> option;

                if (option == 1)
                {
                    layoverQueue.findFlightsWithLayovers(origin, destination, date, g);
                }
                else if (option == 2)
                {
                    g.findShortestPath(origin, destination);  // Finds shortest path considering layovers
                }
                else if (option == 3)
                {
                    g.findCheapestPath(origin, destination);
                }
                else
                {
                    cout << "Invalid choice. Please try again.\n";
                }
            }
            break;
        }
        case 3:
        {
            cout << "Exiting..." << endl;

            cout << BLUE << "     ***      *******   *******   *******    *******   ***     ***    *******" << endl;
            cout << "    *****     **   **   **   **   **    **   **   **    ***   ***     **" << endl;
            cout << "   **         **   **   **   **   **     **  **   **     *******      **" << endl;
            cout << "  **   ****   **   **   **   **   **      ** *******       ***        *******" << endl;
            cout << "   **  ****   **   **   **   **   **     **  **   **       ***        **" << endl;
            cout << "    *****     **   **   **   **   **    **   **   **       ***        **" << endl;
            cout << "     ***      *******   *******   *******    *******       ***        *******" << RESET << endl;
            running = false;
            break;
        }
        default:
        {
            cout << "Invalid choice. Please try again.\n";
            break;
        }
        }
    }

    return 0;
}
