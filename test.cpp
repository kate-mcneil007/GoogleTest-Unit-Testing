// Uncomment the next line to use precompiled headers
#include "pch.h"
#include <utility>
#include <iostream>
// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
//TEST_F(CollectionTest, AlwaysFail)
//{
//    FAIL();
//}

// TODO: Create a test to verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // Assert collection is empty and size 0
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);

    // Add a single value 
    add_entries(1);

    // Assert collection no longer empty and size 1
    ASSERT_FALSE(collection->empty());
    ASSERT_EQ(collection->size(), 1);

}

// TODO: Create a test to verify adding five values to collection
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    // Add 5 entries
    add_entries(5);

    // Does collection size equal 5? 
    // If equal then 5 values were added
    ASSERT_EQ(collection->size(), 5);
}

// TODO: Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, VerifyMaxSize)
{
    // Check to see if collection size is 0
    // Assert that max size is greater than or equal to size for 0 entries 
    ASSERT_EQ(collection->size(), 0);
    ASSERT_TRUE(collection->max_size() >= collection->size());
    std::cout << "Max size " << collection->max_size() << " >= " << collection->size() << " Entries" << std::endl;

    // 1 entry
    // Assert that max size is greater than or equal to size for 1 entry 
    add_entries(1);
    ASSERT_TRUE(collection->max_size() >= collection->size());
    std::cout << "Max size " << collection->max_size() << " >= " << collection->size() << " Entries" << std::endl;

    // 5 entries
    // Assert that max size is greater than or equal to size for 5 entries
    add_entries(4);
    ASSERT_TRUE(collection->max_size() >= collection->size());
    std::cout << "Max size " << collection->max_size() << " >= " << collection->size() << " Entries" << std::endl;

    // 10 entries 
    // Assert that max size is greater than or equal to size for 5 entries
    add_entries(5);
    ASSERT_TRUE(collection->max_size() >= collection->size());
    std::cout << "Max size " << collection->max_size() << " >= " << collection->size() << " Entries" << std::endl;
}

// TODO: Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, VerifyCapactity)
{
    // Check to see if collection size is 0
    // Assert that capacity is greater than or equal to size for 0 entries 
    ASSERT_EQ(collection->size(), 0);
    ASSERT_TRUE(collection->capacity() >= collection->size());
    std::cout << "Capacity size " << collection->capacity() << " >= " << collection->size() << " Entries" << std::endl;

    // 1 entry
    // Assert that capacity is greater than or equal to size for 1 entry 
    add_entries(1);
    ASSERT_TRUE(collection->capacity() >= collection->size());
    std::cout << "Capacity size " << collection->capacity() << " >= " << collection->size() << " Entries" << std::endl;

    // 5 entries
    // Assert that capacity is greater than or equal to size for 5 entries
    add_entries(4);
    ASSERT_TRUE(collection->capacity() >= collection->size());
    std::cout << "Capacity size " << collection->capacity() << " >= " << collection->size() << " Entries" << std::endl;

    // 10 entries 
    // Assert that capacity is greater than or equal to size for 5 entries
    add_entries(5);
    ASSERT_TRUE(collection->capacity() >= collection->size());
    std::cout << "Capacity size " << collection->capacity() << " >= " << collection->size() << " Entries" << std::endl;
}

// TODO: Create a test to verify resizing increases the collection
TEST_F(CollectionTest, VerifyCollectionSizeIncrease)
{
    // Set variable equal to current size of collection 
    int startSize = collection->size();

    // Increase entries 
    collection->resize(10);

    // Assert that resizing increases the collection
    ASSERT_TRUE(collection->size() > startSize);
    std::cout << "Current size " << collection->size() << " > " << startSize << " Entries before increasing size" << std::endl;

}

// TODO: Create a test to verify resizing decreases the collection
TEST_F(CollectionTest, VerifyCollectionSizeDecrease)
{
    // Add entries to collection 
    add_entries(10);
    // Set variable equal to current size of collection 
    int startSize = collection->size();

    // Decrease entries 
    collection->resize(5);

    // Assert that resizing decreases the collection
    ASSERT_TRUE(collection->size() < startSize);
    std::cout << "Current size " << collection->size() << " < " << startSize << " Entries before decreasing size" << std::endl;
}

// TODO: Create a test to verify resizing decreases the collection to zero
TEST_F(CollectionTest, VerifyCollectionSizeZero)
{
    // Add entries to collection 
    add_entries(10);

    // Decrease entries 
    collection->resize(0);

    // Assert that resizing increases the collection to zero
    ASSERT_EQ(collection->size(), 0);
    std::cout << "Current size " << collection->size() << " = 0" << std::endl;
}

// TODO: Create a test to verify clear erases the collection
TEST_F(CollectionTest, VerifyClearErases)
{
    // Add entries to collection 
    add_entries(10);

    // Clear entries 
    collection->clear();

    // Assert that clear erases the collection
    ASSERT_EQ(collection->size(), 0);
    std::cout << "Current size " << collection->size() << std::endl;
}

// Positive test
TEST_F(CollectionTest, CollectionSmartPointerIsNull)
{
    // Add entries to collection 
    add_entries(10);

    // Clear entries 
    collection->clear();

    // Assert that clear erases the collection
    ASSERT_TRUE(collection.get(), nullptr);
}

// TODO: Create a test to verify erase(begin,end) erases the collection
TEST_F(CollectionTest, VerifyErase)
{
    // Add entries to collection 
    add_entries(10);

    // Clear entries 
    collection->erase(collection->begin(), collection->end());

    // Assert that clear erases the collection
    ASSERT_EQ(collection->size(), 0);
    std::cout << "Current size " << collection->size() << std::endl;
}

// TODO: Create a test to verify reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, VerifyCapacityNotSize)
{
    // Add entries to collection 
    add_entries(10);
    // Set variable equal to current size of collection 
    int startSize = collection->size();
    int startCapacity = collection->capacity();

    // Reserve a capacity of 20
    collection->reserve(20);

    // Assert that current capacity is larger than original capacity, and current size equals original size 
    ASSERT_TRUE(collection->capacity() > startCapacity);
    ASSERT_TRUE(collection->size() == startSize);

    std::cout << "Initial size: " << startSize << std::endl;
    std::cout << "Initial capacity: " << startCapacity << std::endl;
    std::cout << "Current size: " << collection->size() << std::endl;
    std::cout << "Current capacity: " << collection->capacity() << std::endl;
}

// Verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
// NOTE: This is a negative test
TEST_F(CollectionTest, VerifyExceptionThrown)
{
    std::vector<int> indexSize(20);
    
    // Check if throws exception when index out of bounds 
    EXPECT_THROW(indexSize.at(25), std::out_of_range);
}

// Test that verifies length error is thrown when try to expand collection size past capacity
// Negative test 
TEST_F(CollectionTest, ReserveLengthTooLong)
{
    // Reserve a # larger than capacity, length error thrown 
    EXPECT_THROW(collection->reserve(9999999999), std::length_error);
    std::cout << "Too long!" << std::endl;
}

// Test that push_back adds to the size of the collection 
// Positive test 
TEST_F(CollectionTest, PushBackAddsVal)
{
    // Add entries to collection 
    add_entries(10);
    // Set variable equal to current size of collection 
    int startSize = collection->size();

    collection->push_back(rand() % 100);
    // Set variable equal to new size of collection
    int pushBackSize = collection->size();

    ASSERT_TRUE(pushBackSize > startSize);
    std::cout << "The collection was " << startSize << " and now it is " << pushBackSize << std::endl;
}

// Negative test
/*
TEST_F(CollectionTest, MemoryTest)
{
    int* pointer1 = new int;
    int* pointer2 = new int;

    std::shared_ptr<int> smartPointer1(pointer1);
    std::shared_ptr<int> smartPointer2(pointer2);

    ASSERT_NE(smartPointer1, pointer2);
}*/