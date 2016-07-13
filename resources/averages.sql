SELECT simulationName, correlationFile, permutationIndex, COUNT(*) AS numDataSets, AVG(averageComputationTime), AVG(minComputationTime), AVG(maxComputationTime), AVG(totalComputationTime),
AVG(averageMemory), AVG(minMemory), AVG(maxMemory) , (AVG(maxMemory) - AVG(minMemory)) AS memoryDiff,
AVG(leftSteerings), AVG(rightSteerings), (AVG(leftSteerings)  + AVG(rightSteerings)) AS totalSteerings,
AVG(averageLeftSteeringAngle), AVG(averageRightSteeringAngle), AVG(ABS(maxSteeringAngle)), MAX(maxSteeringAngle) FROM simulationdata GROUP BY simulationName, correlationFile, permutationIndex