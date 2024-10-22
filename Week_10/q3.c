#include <stdio.h>
#include <stdlib.h>
typedef struct 
{
    int start;  
    int end; 
} SegmentTableEntry;
int logicalToPhysical(int segment, int offset, SegmentTableEntry segmentTable[], int numSegments);
int main() 
{
    int numSegments = 5;
    SegmentTableEntry segmentTable[5] = 
    {
        {1400, 2400},  
        {6300, 6700},  
        {4300, 4700},  
        {3200, 4300},  
        {4700, 5700}   
    };
    int segment, offset;
    segment = 2;
    offset = 53;
    printf("Physical address for %d byte of segment %d: %d\n", offset, segment, logicalToPhysical(segment, offset, segmentTable, numSegments));
    segment = 3;
    offset = 852;
    printf("Physical address for %d byte of segment %d: %d\n", offset, segment, logicalToPhysical(segment, offset, segmentTable, numSegments));
    segment = 0;
    offset = 1222;
    printf("Physical address for %d byte of segment %d: %d\n", offset, segment, logicalToPhysical(segment, offset, segmentTable, numSegments));
    return 0;
}

int logicalToPhysical(int segment, int offset, SegmentTableEntry segmentTable[], int numSegments) 
{
    if (segment < 0 || segment >= numSegments) 
    {
        printf("Error: Invalid segment number\n");
        exit(1);
    }
    int start = segmentTable[segment].start;
    int end = segmentTable[segment].end;
    if (offset >= 0 && offset < end-start) 
    {
        return start + offset;
    } 
    else 
    {
        printf("Error: Offset %d out of bounds for segment %d (limit %d)\n", offset, segment, end-start);
    }
}
