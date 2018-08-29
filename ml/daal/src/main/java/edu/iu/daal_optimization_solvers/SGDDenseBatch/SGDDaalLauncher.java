/*
 * Copyright 2013-2016 Indiana University
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

package edu.iu.daal_optimization_solvers.SGDDenseBatch;

import edu.iu.fileformat.MultiFileInputFormat;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.conf.Configured;
import org.apache.hadoop.filecache.DistributedCache;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.mapred.JobConf;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.util.Tool;
import org.apache.hadoop.util.ToolRunner;

import edu.iu.data_aux.*;

import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.concurrent.ExecutionException;

public class SGDDaalLauncher extends Configured
  implements Tool {

  public static void main(String[] argv)
    throws Exception {
    int res =
      ToolRunner.run(new Configuration(),
        new SGDDaalLauncher(), argv);
    System.exit(res);
  }

  /**
   * Launches all the tasks in order.
   */
  @Override
  public int run(String[] args) throws Exception {

      /* Put shared libraries into the distributed cache */
      Configuration conf = this.getConf();

      Initialize init = new Initialize(conf, args);

      /* Put shared libraries into the distributed cache */
      init.loadDistributedLibs();

      // load args
      init.loadSysArgs();

      conf.setInt(HarpDAALConstants.FILE_DIM, Integer.parseInt(args[init.getSysArgNum()]));
      conf.setInt(HarpDAALConstants.FEATURE_DIM, Integer.parseInt(args[init.getSysArgNum()+1]));
      conf.setDouble(HarpDAALConstants.ACC_THRESHOLD, Double.parseDouble(args[init.getSysArgNum()+2]));
      conf.setDouble(HarpDAALConstants.LEARNING_RATE, Double.parseDouble(args[init.getSysArgNum()+3]));

      // launch job
      System.out.println("Starting Job");
      long perJobSubmitTime = System.currentTimeMillis();
      System.out.println("Start Job#"  + " "+ new SimpleDateFormat("HH:mm:ss.SSS").format(Calendar.getInstance().getTime()));

      Job sgdJob = init.createJob("sgdJob", SGDDaalLauncher.class, SGDDaalCollectiveMapper.class); 

      // finish job
      boolean jobSuccess = sgdJob.waitForCompletion(true);
      System.out.println("End Job#"  + " "+ new SimpleDateFormat("HH:mm:ss.SSS").format(Calendar.getInstance().getTime()));
      System.out.println("| Job#"  + " Finished in " + (System.currentTimeMillis() - perJobSubmitTime)+ " miliseconds |");
      if (!jobSuccess) {
	      sgdJob.killJob();
	      System.out.println("sgdJob failed");
      }

    return 0;
  }


}
