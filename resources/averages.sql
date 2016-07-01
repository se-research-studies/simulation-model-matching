SELECT AVG(averageComputationTime), AVG(minComputationTime), AVG(maxComputationTime), AVG(totalComputationTime),
AVG(leftSteerings), AVG(rightSteerings), (AVG(leftSteerings)  + AVG(rightSteerings)) AS totalSteerings,
AVG(averageMemory), AVG(minMemory), AVG(maxMemory) , (AVG(maxMemory) - AVG(minMemory)) AS memoryDiff FROM simulationdata GROUP BY correlationFile