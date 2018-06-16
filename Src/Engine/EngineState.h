#pragma once

// free list interface for the data
struct SystemsInterface;

struct SystemsData;

struct SystemsInterface initializeSystemInterface();
void freeSystemInterface();
