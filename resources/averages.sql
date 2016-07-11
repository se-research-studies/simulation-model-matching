SELECT simulationName, correlationFile, permutationIndex, AVG(averageComputationTime), AVG(minComputationTime), AVG(maxComputationTime), AVG(totalComputationTime),
AVG(averageMemory), AVG(minMemory), AVG(maxMemory) , (AVG(maxMemory) - AVG(minMemory)) AS memoryDiff,
AVG(leftSteerings), AVG(rightSteerings), (AVG(leftSteerings)  + AVG(rightSteerings)) AS totalSteerings,
AVG(averageLeftSteeringAngle), AVG(averageRightSteeringAngle), AVG(maxSteeringAngle), MAX(maxSteeringAngle) FROM simulationdata GROUP BY simulationName, correlationFile, permutationIndex