#include <unity.h>
#include "TrinovaVision.h"

TrinovaVision vision;

void setUp(void) {
    vision.begin(VisionMode::Mock);
    vision.setConfidence(0);  // pas de filtrage par defaut, sauf si un test le change lui-meme
}

void tearDown(void) {
    // rien a nettoyer pour l'instant
}

void test_person_left(void) {
    vision.setMockScenario(MockScenario::PersonLeft);
    VisionResult result = vision.read();

    TEST_ASSERT_TRUE(result.connected);
    TEST_ASSERT_TRUE(result.detected);
    TEST_ASSERT_EQUAL(1, result.count);
    TEST_ASSERT_EQUAL(92, result.objects[0].confidence);
    TEST_ASSERT_EQUAL(50, result.objects[0].x);
    TEST_ASSERT_EQUAL_STRING("person", result.objects[0].label);
}

void test_person_center(void) {
    vision.setMockScenario(MockScenario::PersonCenter);
    VisionResult result = vision.read();

    TEST_ASSERT_TRUE(result.connected);
    TEST_ASSERT_TRUE(result.detected);
    TEST_ASSERT_EQUAL(1, result.count);
    TEST_ASSERT_EQUAL_STRING("person", result.objects[0].label);
    TEST_ASSERT_EQUAL(160, result.objects[0].x);
}

void test_no_detection(void) {
    vision.setMockScenario(MockScenario::NoDetection);
    VisionResult result = vision.read();

    TEST_ASSERT_TRUE(result.connected);
    TEST_ASSERT_FALSE(result.detected);
    TEST_ASSERT_EQUAL(0, result.count);
}

void test_multiple_objects(void) {
    vision.setMockScenario(MockScenario::MultipleObjects);
    VisionResult result = vision.read();

    TEST_ASSERT_TRUE(result.connected);
    TEST_ASSERT_TRUE(result.detected);
    TEST_ASSERT_EQUAL(3, result.count);
    TEST_ASSERT_TRUE(result.count <= TRINOVA_MAX_OBJECTS);
}

void test_low_confidence_is_filtered(void) {
    vision.setConfidence(80);   // seuil volontairement eleve pour ce test
    vision.setMockScenario(MockScenario::LowConfidence);
    VisionResult result = vision.read();

    TEST_ASSERT_TRUE(result.connected);
    TEST_ASSERT_FALSE(result.detected);   // 40% < 80% -> filtre, donc rien ne doit rester
    TEST_ASSERT_EQUAL(0, result.count);

    vision.setConfidence(0);   // on remet a zero pour ne pas fausser les tests suivants
}

void test_disconnected(void) {
    vision.setMockScenario(MockScenario::Disconnected);
    VisionResult result = vision.read();

    TEST_ASSERT_FALSE(result.connected);
    TEST_ASSERT_FALSE(result.success);
}

void test_timeout(void) {
    vision.setMockScenario(MockScenario::Timeout);
    VisionResult result = vision.read();

    TEST_ASSERT_TRUE(result.connected);
    TEST_ASSERT_FALSE(result.success);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_person_left);
    RUN_TEST(test_person_center);
    RUN_TEST(test_no_detection);
    RUN_TEST(test_multiple_objects);
    RUN_TEST(test_low_confidence_is_filtered);
    RUN_TEST(test_disconnected);
    RUN_TEST(test_timeout);
    UNITY_END();
    return 0;
}