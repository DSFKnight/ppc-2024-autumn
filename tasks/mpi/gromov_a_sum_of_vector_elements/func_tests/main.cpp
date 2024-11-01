#include <gtest/gtest.h>

#include <boost/mpi/communicator.hpp>
#include <boost/mpi/environment.hpp>
#include <vector>

#include "mpi/gromov_a_sum_of_vector_elements/include/ops_mpi.hpp"

TEST(gromov_a_sum_of_vector_elements_mpi, Test_Product) {
  boost::mpi::communicator world;
  std::vector<int> global_vec;
  std::vector<int32_t> global_product(1, 1);
  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataPar = std::make_shared<ppc::core::TaskData>();

  if (world.rank() == 0) {
    const int count_size_vector = 100;
    global_vec = gromov_a_sum_of_vector_elements_mpi::getRandomVector(count_size_vector);
    taskDataPar->inputs.emplace_back(reinterpret_cast<uint8_t*>(global_vec.data()));
    taskDataPar->inputs_count.emplace_back(global_vec.size());
    taskDataPar->outputs.emplace_back(reinterpret_cast<uint8_t*>(global_product.data()));
    taskDataPar->outputs_count.emplace_back(global_product.size());
  }

  gromov_a_sum_of_vector_elements_mpi::MPISumOfVectorParallel MPISumOfVectorParallel(taskDataPar, "*");
  ASSERT_EQ(MPISumOfVectorParallel.validation(), true);
  MPISumOfVectorParallel.pre_processing();
  MPISumOfVectorParallel.run();
  MPISumOfVectorParallel.post_processing();

  if (world.rank() == 0) {
    // Create data
    std::vector<int32_t> reference_product(1, 1);

    // Create TaskData
    std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
    taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t*>(global_vec.data()));
    taskDataSeq->inputs_count.emplace_back(global_vec.size());
    taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t*>(reference_product.data()));
    taskDataSeq->outputs_count.emplace_back(reference_product.size());

    // Create Task
    gromov_a_sum_of_vector_elements_mpi::MPISumOfVectorSequential MPISumOfVectorSequential(taskDataSeq, "*");
    ASSERT_EQ(MPISumOfVectorSequential.validation(), true);
    MPISumOfVectorSequential.pre_processing();
    MPISumOfVectorSequential.run();
    MPISumOfVectorSequential.post_processing();

    ASSERT_EQ(reference_product[0], global_product[0]);
  }
}

TEST(gromov_a_sum_of_vector_elements_mpi, Test_Min) {
  boost::mpi::communicator world;
  std::vector<int> global_vec;
  std::vector<int32_t> global_min(1, std::numeric_limits<int32_t>::max());
  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataPar = std::make_shared<ppc::core::TaskData>();

  if (world.rank() == 0) {
    const int count_size_vector = 150;
    global_vec = gromov_a_sum_of_vector_elements_mpi::getRandomVector(count_size_vector);
    taskDataPar->inputs.emplace_back(reinterpret_cast<uint8_t*>(global_vec.data()));
    taskDataPar->inputs_count.emplace_back(global_vec.size());
    taskDataPar->outputs.emplace_back(reinterpret_cast<uint8_t*>(global_min.data()));
    taskDataPar->outputs_count.emplace_back(global_min.size());
  }

  gromov_a_sum_of_vector_elements_mpi::MPISumOfVectorParallel MPISumOfVectorParallel(taskDataPar, "min");
  ASSERT_EQ(MPISumOfVectorParallel.validation(), true);
  MPISumOfVectorParallel.pre_processing();
  MPISumOfVectorParallel.run();
  MPISumOfVectorParallel.post_processing();

  if (world.rank() == 0) {
    // Create data
    std::vector<int32_t> reference_min(1, std::numeric_limits<int32_t>::max());

    // Create TaskData
    std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
    taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t*>(global_vec.data()));
    taskDataSeq->inputs_count.emplace_back(global_vec.size());
    taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t*>(reference_min.data()));
    taskDataSeq->outputs_count.emplace_back(reference_min.size());

    // Create Task
    gromov_a_sum_of_vector_elements_mpi::MPISumOfVectorSequential MPISumOfVectorSequential(taskDataSeq, "min");
    ASSERT_EQ(MPISumOfVectorSequential.validation(), true);
    MPISumOfVectorSequential.pre_processing();
    MPISumOfVectorSequential.run();
    MPISumOfVectorSequential.post_processing();

    ASSERT_EQ(reference_min[0], global_min[0]);
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

TEST(gromov_a_sum_of_vector_elements_mpi, Test_Min2) {
  boost::mpi::communicator world;
  std::vector<int> global_vec;
  std::vector<int32_t> global_min(1, std::numeric_limits<int32_t>::max());
  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataPar = std::make_shared<ppc::core::TaskData>();

  if (world.rank() == 0) {
    const int count_size_vector = 150;
    global_vec = gromov_a_sum_of_vector_elements_mpi::getRandomVector(count_size_vector);
    taskDataPar->inputs.emplace_back(reinterpret_cast<uint8_t*>(global_vec.data()));
    taskDataPar->inputs_count.emplace_back(global_vec.size());
    taskDataPar->outputs.emplace_back(reinterpret_cast<uint8_t*>(global_min.data()));
    taskDataPar->outputs_count.emplace_back(global_min.size());
  }

  gromov_a_sum_of_vector_elements_mpi::MPISumOfVectorParallel MPISumOfVectorParallel(taskDataPar, "min");
  ASSERT_EQ(MPISumOfVectorParallel.validation(), true);
  MPISumOfVectorParallel.pre_processing();
  MPISumOfVectorParallel.run();
  MPISumOfVectorParallel.post_processing();

  if (world.rank() == 0) {
    // Create data
    std::vector<int32_t> reference_min(1, std::numeric_limits<int32_t>::max());

    // Create TaskData
    std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
    taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t*>(global_vec.data()));
    taskDataSeq->inputs_count.emplace_back(global_vec.size());
    taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t*>(reference_min.data()));
    taskDataSeq->outputs_count.emplace_back(reference_min.size());

    // Create Task
    gromov_a_sum_of_vector_elements_mpi::MPISumOfVectorSequential MPISumOfVectorSequential(taskDataSeq, "min");
    ASSERT_EQ(MPISumOfVectorSequential.validation(), true);
    MPISumOfVectorSequential.pre_processing();
    MPISumOfVectorSequential.run();
    MPISumOfVectorSequential.post_processing();

    ASSERT_EQ(reference_min[0], global_min[0]);
  }
}
