/*
 * Copyright 2013-2017 Indiana University
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package edu.iu.examples;

import java.util.logging.Logger;

/**
 * Captures parameters for running the examples
 */
public class ExampleParameters {
  private static final Logger LOG = Logger.getLogger(ExampleParameters.class.getName());
  private int size;

  private int iterations;

  private String operation;

  private int mappers = 0;

  private int partitions = 0;

  private String dataType;

  public ExampleParameters(int mappers, int size, int iterations,
                           String operation, int partitions, String dataType) {
    this.size = size;
    this.iterations = iterations;
    this.operation = operation;
    this.mappers = mappers;
    this.partitions = partitions;
    this.dataType = dataType;
  }

  public int getSize() {
    return size;
  }

  public int getIterations() {
    return iterations;
  }

  public String getOperation() {
    return operation;
  }

  public int getMappers() {
    return mappers;
  }

  public int getPartitions() {
    return partitions;
  }

  public String getDataType() {
    return dataType;
  }
}
