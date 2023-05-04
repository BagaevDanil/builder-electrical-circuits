#include <gtest/gtest.h>
#include "../src/chainitem.h"

TEST(ChainItem, create1) {
    QString str = "K1-L2-K3-(K4-L5-K6,K7-L8-K9,(K10-L11,K12-L13-K14),(K15-L16-K17))-(K18-L19,L20-K21)-L22-K23-L24-K25";
    QString ans = "K1->L2->K3->{K4->L5->K6, K7->L8->K9, {K10->L11, K12->L13->K14}, {K15->L16->K17}}->{K18->L19, L20->K21}->L22->K23->L24->K25";
    QString ansR = "K25->L24->K23->L22->{L19->K18, K21->L20}->{K6->L5->K4, K9->L8->K7, {L11->K10, K14->L13->K12}, {K17->L16->K15}}->K3->L2->K1";
    TChainItem chain(str, nullptr, 0, 0);

    QString prediction = chain.ToString();
    chain.SetReverse(true);
    QString predictionR =  chain.ToString();

    ASSERT_EQ(prediction, ans);
    ASSERT_EQ(predictionR, ansR);
}

TEST(ChainItem, create2) {
    QString str1 = "K1-L2-K3-(K4-L5-/K6,K7-L8-K9,(K10-L11,K12-L13-K14),(K15-L16-K17))-(K18-L19,L20-K21)-L22-K23-L24-K25";
    QString str2 = "K1-L2-K3-((K4-L5-K6,K7-L8-K9,(K10-L11,K12-L13-K14),(K15-L16-K17))-(K18-L19,L20-K21)-L22-K23-L24-K25";
    QString str3 = "U1-L2-K3-((K4-L5-K6,K7-L8-K9,(K10-L11,K12-L13-K14),(K15-L16-K17))-(K18-L19,L20-K21)-L22-K23-L24-K25";
    QString str4 = "";

    ASSERT_THROW(new TChainItem(str1, nullptr, 0, 0), std::exception);
    ASSERT_THROW(new TChainItem(str2, nullptr, 0, 0), std::exception);
    ASSERT_THROW(new TChainItem(str3, nullptr, 0, 0), std::exception);
    ASSERT_THROW(new TChainItem(str4, nullptr, 0, 0), std::exception);
}

int main()
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
