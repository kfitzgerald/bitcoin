// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "assert.h"
#include "core.h"
#include "protocol.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

//
// Main network
//

unsigned int pnSeed[] =
{
    0x42b91f24, // seed1.titcoin.soarcetech.com
    0x42b91f22  // seed2.titcoin.soarcetech.com
};

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x86; //86 => †
        pchMessageStart[1] = 0xee; //ee => î
        pchMessageStart[2] = 0x86; //86 => †
        pchMessageStart[3] = 0x99; //99 => ™
        vAlertPubKey = ParseHex("0423a788d9131c1627fbcd8492c6aabdb0ab19118a6f5dc5b751dfce791657a927a68f1a73b1fd4b80337da5f429591b8fa9a0ef7bcf73d0c3ca237e4aa800e074");
        nDefaultPort = 57173;
        nRPCPort = 57172;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 32);
        nSubsidyHalvingInterval = 210000;

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //
        const char* pszTimestamp = "Horizon - Richard Dawkins 13/Apr/1986 Nice Guys Finish First";
        CTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CBigNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 50 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04724e30d26668117a39d62e5c96ea9462437f6a198d206329297a5aa61e363a6ea47f2467c3e64dcf1de8c1fa689ded52d8b90371ca9fdccfe28521cb48d60754") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 513820802;
        genesis.nBits    = 0x1d00ffff;
        genesis.nNonce   = 1086568413;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000000574cadf67dde5965187520ea5235bd14a6468e1a9a98d1ea83269694"));
        assert(genesis.hashMerkleRoot == uint256("0xf8a5872ca6bd520e58ddc3a3de9092903caebb03d11d9e62561f10c43f3675f9"));

        // vSeeds.push_back(CDNSSeedData("bitcoin.sipa.be", "seed.bitcoin.sipa.be"));
        // vSeeds.push_back(CDNSSeedData("bluematt.me", "dnsseed.bluematt.me"));
        // vSeeds.push_back(CDNSSeedData("dashjr.org", "dnsseed.bitcoin.dashjr.org"));
        // vSeeds.push_back(CDNSSeedData("bitcoinstats.com", "seed.bitcoinstats.com"));
        // vSeeds.push_back(CDNSSeedData("xf2.org", "bitseed.xf2.org"));
		vSeeds.push_back(CDNSSeedData("soarcetech.com", "seed.titcoin.soarcetech.com"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(127); // t
        base58Prefixes[SCRIPT_ADDRESS] = list_of(130); // u
        base58Prefixes[SECRET_KEY] =     list_of(132); // v
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x8c)(0xB6)(0x2b);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x8c)(0xB2)(0xE8);

        // Convert the pnSeeds array into usable address objects.
        for (unsigned int i = 0; i < ARRAYLEN(pnSeed); i++)
        {
            // It'll only connect to one or two seed nodes because once it connects,
            // it'll get a pile of addresses with newer timestamps.
            // Seed nodes are given a random 'last seen time' of between one and two
            // weeks ago.
            const int64_t nOneWeek = 7*24*60*60;
            struct in_addr ip;
            memcpy(&ip, &pnSeed[i], sizeof(ip));
            CAddress addr(CService(ip, GetDefaultPort()));
            addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
            vFixedSeeds.push_back(addr);
        }
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet (v3)
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x83; //83 => ƒ
        pchMessageStart[1] = 0xef; //ef => ï
        pchMessageStart[2] = 0x86; //86 => †
        pchMessageStart[3] = 0x9e; //9e => ž
        vAlertPubKey = ParseHex("0454577279b63301be0edc364e92b97837dda3e41519c029422a04d673223166c310b7601f42d3b9ed803c24d79beb8f5012c0d1e9d3630e2206cba5c9327e60d7");
        nDefaultPort = 57175;
        nRPCPort = 57174;
        strDataDir = "testnet3";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 513820825;
        genesis.nNonce = 1846343381;
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000000aceaeb862007902257378f1b62ae7a377ed57f7bd76f2d1409583155"));

        vFixedSeeds.clear();
        vSeeds.clear();
//        vSeeds.push_back(CDNSSeedData("bitcoin.petertodd.org", "testnet-seed.bitcoin.petertodd.org"));
//        vSeeds.push_back(CDNSSeedData("bluematt.me", "testnet-seed.bluematt.me"));
        vSeeds.push_back(CDNSSeedData("soarcetech.com", "testnet-seed.titcoin.soarcetech.com"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(135); // w
        base58Prefixes[SCRIPT_ADDRESS] = list_of(137); // x
        base58Prefixes[SECRET_KEY]     = list_of(140); // y
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x8B)(0xD3);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x87)(0x98);
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xb1;
        pchMessageStart[1] = 0x6b;
        pchMessageStart[2] = 0x00;
        pchMessageStart[3] = 0xb5; // classic, couldn't resist
        nSubsidyHalvingInterval = 150;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1391565998;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 0;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 57176;
        strDataDir = "regtest";
        assert(hashGenesisBlock == uint256("0x472872427dfb9189286d6870053147893c5d92b1dd1c7a7c9cf461450c09ec82"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
