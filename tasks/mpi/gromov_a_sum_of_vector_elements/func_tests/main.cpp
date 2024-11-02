#include <gtest/gtest.h>

#include <boost/mpi/communicator.hpp>
#include <boost/mpi/environment.hpp>
#include <vector>

#include "mpi/gromov_a_sum_of_vector_elements/include/ops_mpi.hpp"

TEST(gromov_a_sum_of_vector_elements_mpi, Test_Average) {
  boost::mpi::communicator world;
  std::vector<int> global_vec;
  std::vector<int32_t> global_average(1, 0);
  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataPar = std::make_shared<ppc::core::TaskData>();

  if (world.rank() == 0) {
    const int count_size_vector = 100;
    global_vec = gromov_a_sum_of_vector_elements_mpi::getRandomVector(count_size_vector);
    taskDataPar->inputs.emplace_back(reinterpret_cast<uint8_t*>(global_vec.data()));
    taskDataPar->inputs_count.emplace_back(global_vec.size());
    taskDataPar->outputs.emplace_back(reinterpret_cast<uint8_t*>(global_average.data()));
    taskDataPar->outputs_count.emplace_back(global_average.size());
  }

  gromov_a_sum_of_vector_elements_mpi::MPISumOfVectorParallel MPISumOfVectorParallel(taskDataPar, "avg");
  ASSERT_EQ(MPISumOfVectorParallel.validation(), true);
  MPISumOfVectorParallel.pre_processing();
  MPISumOfVectorParallel.run();
  MPISumOfVectorParallel.post_processing();

  if (world.rank() == 0) {
    // Create data
    std::vector<int32_t> reference_average(1, 1);

    // Create TaskData
    std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
    taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t*>(global_vec.data()));
    taskDataSeq->inputs_count.emplace_back(global_vec.size());
    taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t*>(reference_average.data()));
    taskDataSeq->outputs_count.emplace_back(reference_average.size());

    // Create Task
    gromov_a_sum_of_vector_elements_mpi::MPISumOfVectorSequential MPISumOfVectorSequential(taskDataSeq, "avg");
    ASSERT_EQ(MPISumOfVectorSequential.validation(), true);
    MPISumOfVectorSequential.pre_processing();
    MPISumOfVectorSequential.run();
    MPISumOfVectorSequential.post_processing();

    ASSERT_EQ(reference_average[0], global_average[0]);
  }
}

TEST(gromov_a_sum_of_vector_elements_mpi, Test_Subtraction) {
  boost::mpi::communicator world;
  std::vector<int> global_vec;
  std::vector<int32_t> global_sub(1, 0);
  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataPar = std::make_shared<ppc::core::TaskData>();

  if (world.rank() == 0) {
    const int count_size_vector = 150;
    global_vec = gromov_a_sum_of_vector_elements_mpi::getRandomVector(count_size_vector);
    taskDataPar->inputs.emplace_back(reinterpret_cast<uint8_t*>(global_vec.data()));
    taskDataPar->inputs_count.emplace_back(global_vec.size());
    taskDataPar->outputs.emplace_back(reinterpret_cast<uint8_t*>(global_sub.data()));
    taskDataPar->outputs_count.emplace_back(global_sub.size());
  }

  gromov_a_sum_of_vector_elements_mpi::MPISumOfVectorParallel MPISumOfVectorParallel(taskDataPar, "sub");
  ASSERT_EQ(MPISumOfVectorParallel.validation(), true);
  MPISumOfVectorParallel.pre_processing();
  MPISumOfVectorParallel.run();
  MPISumOfVectorParallel.post_processing();

  if (world.rank() == 0) {
    // Create data
    std::vector<int32_t> reference_sub(1, 0);

    // Create TaskData
    std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
    taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t*>(global_vec.data()));
    taskDataSeq->inputs_count.emplace_back(global_vec.size());
    taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t*>(reference_sub.data()));
    taskDataSeq->outputs_count.emplace_back(reference_sub.size());

    // Create Task
    gromov_a_sum_of_vector_elements_mpi::MPISumOfVectorSequential MPISumOfVectorSequential(taskDataSeq, "sub");
    ASSERT_EQ(MPISumOfVectorSequential.validation(), true);
    MPISumOfVectorSequential.pre_processing();
    MPISumOfVectorSequential.run();
    MPISumOfVectorSequential.post_processing();

    ASSERT_EQ(reference_sub[0], global_sub[0]);
  }
}

TEST(gromov_a_sum_of_vector_elements_mpi, Test_Max) {
  boost::mpi::communicator world;
  std::vector<int> global_vec;
  std::vector<int32_t> global_max(1, std::numeric_limits<int32_t>::min());
  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataPar = std::make_shared<ppc::core::TaskData>();

  if (world.rank() == 0) {
    const int count_size_vector = 150;
    global_vec = gromov_a_sum_of_vector_elements_mpi::getRandomVector(count_size_vector);
    taskDataPar->inputs.emplace_back(reinterpret_cast<uint8_t*>(global_vec.data()));
    taskDataPar->inputs_count.emplace_back(global_vec.size());
    taskDataPar->outputs.emplace_back(reinterpret_cast<uint8_t*>(global_max.data()));
    taskDataPar->outputs_count.emplace_back(global_max.size());
  }

  gromov_a_sum_of_vector_elements_mpi::MPISumOfVectorParallel MPISumOfVectorParallel(taskDataPar, "max");
  ASSERT_EQ(MPISumOfVectorParallel.validation(), true);
  MPISumOfVectorParallel.pre_processing();
  MPISumOfVectorParallel.run();
  MPISumOfVectorParallel.post_processing();

  if (world.rank() == 0) {
    // Create data
    std::vector<int32_t> reference_max(1, std::numeric_limits<int32_t>::min());

    // Create TaskData
    std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
    taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t*>(global_vec.data()));
    taskDataSeq->inputs_count.emplace_back(global_vec.size());
    taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t*>(reference_max.data()));
    taskDataSeq->outputs_count.emplace_back(reference_max.size());

    // Create Task
    gromov_a_sum_of_vector_elements_mpi::MPISumOfVectorSequential MPISumOfVectorSequential(taskDataSeq, "max");
    ASSERT_EQ(MPISumOfVectorSequential.validation(), true);
    MPISumOfVectorSequential.pre_processing();
    MPISumOfVectorSequential.run();
    MPISumOfVectorSequential.post_processing();

    ASSERT_EQ(reference_max[0], global_max[0]);
  }
}

TEST(gromov_a_sum_of_vector_elements_mpi, Test_Addition) {
  boost::mpi::communicator world;
  std::vector<int> global_vec;
  std::vector<int32_t> global_add(1, 0);
  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataPar = std::make_shared<ppc::core::TaskData>();

  if (world.rank() == 0) {
    const int count_size_vector = 150;
    global_vec = gromov_a_sum_of_vector_elements_mpi::getRandomVector(count_size_vector);
    taskDataPar->inputs.emplace_back(reinterpret_cast<uint8_t*>(global_vec.data()));
    taskDataPar->inputs_count.emplace_back(global_vec.size());
    taskDataPar->outputs.emplace_back(reinterpret_cast<uint8_t*>(global_add.data()));
    taskDataPar->outputs_count.emplace_back(global_add.size());
  }

  gromov_a_sum_of_vector_elements_mpi::MPISumOfVectorParallel MPISumOfVectorParallel(taskDataPar, "add");
  ASSERT_EQ(MPISumOfVectorParallel.validation(), true);
  MPISumOfVectorParallel.pre_processing();
  MPISumOfVectorParallel.run();
  MPISumOfVectorParallel.post_processing();

  if (world.rank() == 0) {
    // Create data
    std::vector<int32_t> reference_add(1, 0);

    // Create TaskData
    std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
    taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t*>(global_vec.data()));
    taskDataSeq->inputs_count.emplace_back(global_vec.size());
    taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t*>(reference_add.data()));
    taskDataSeq->outputs_count.emplace_back(reference_add.size());

    // Create Task
    gromov_a_sum_of_vector_elements_mpi::MPISumOfVectorSequential MPISumOfVectorSequential(taskDataSeq, "add");
    ASSERT_EQ(MPISumOfVectorSequential.validation(), true);
    MPISumOfVectorSequential.pre_processing();
    MPISumOfVectorSequential.run();
    MPISumOfVectorSequential.post_processing();

    ASSERT_EQ(reference_add[0], global_add[0]);
  }
}