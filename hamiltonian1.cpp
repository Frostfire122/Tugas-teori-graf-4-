#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAX_ROOMS 10
#define MAX_TUNNELS 20

int main() {
    //makes it so random generator differently every run
    srand(time(NULL));

    //randomly decide how many rooms to generate
    int numRooms = 5 + rand() % (MAX_ROOMS - 5 + 1);

    //randomly decide how many tunnels to generate,, between numRooms and MAX_TUNNELS
    int maxPossibleTunnels = numRooms * (numRooms - 1) / 2;  //max edges in a simple graph
    int numTunnels = numRooms + rand() % (maxPossibleTunnels - numRooms + 1);
    if (numTunnels > MAX_TUNNELS) numTunnels = MAX_TUNNELS;

    printf("Generated %d rooms (0 to %d)\n\n", numRooms, numRooms - 1);

    //adjacency matrix to avoid generating duplicate tunnels
    //and to build the per-room listing afterward
    bool tunnelExists[MAX_ROOMS][MAX_ROOMS] = { false };

    int src[MAX_TUNNELS], dest[MAX_TUNNELS];
    int tunnelsMade = 0;
    int attempts = 0;
    int maxAttempts = numTunnels * 20;  //safety limit to avoid infinite loop

    while (tunnelsMade < numTunnels && attempts < maxAttempts) {
        int a = rand() % numRooms;
        int b = rand() % numRooms;

        attempts++;

        //skip if same room, or tunnel already exists (in either direction)
        if (a == b) continue;
        if (tunnelExists[a][b] || tunnelExists[b][a]) continue;

        //record the tunnel
        tunnelExists[a][b] = true;
        tunnelExists[b][a] = true;
        src[tunnelsMade] = a;
        dest[tunnelsMade] = b;
        tunnelsMade++;
    }

    printf("Tunnels: %d total\n\n", tunnelsMade);

    //print each room's connections using the adjacency matrix
    for (int room = 0; room < numRooms; room++) {
        printf("Room %d - ", room);

        bool first = true;
        for (int other = 0; other < numRooms; other++) {
            if (tunnelExists[room][other]) {
                if (!first) printf(", ");
                printf("%d", other);
                first = false;
            }
        }

        if (first) {
            printf("(no connections)");
        }

        printf("\n");
    }

    return 0;
}
