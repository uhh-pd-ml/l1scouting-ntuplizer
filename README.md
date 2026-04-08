# L1Scouting NTuplizer

Conversion of CMS L1 Scouting EDM data into flat ROOT ntuples suitable for modern analysis workflows (e.g. Python, `uproot`, `awkward`, PyTorch).

## Overview

This package provides:

- A **CMSSW EDAnalyzer** that reads L1 Scouting Run-3 data (`OrbitCollection<l1ScoutingRun3::...>`)
- A **Python configuration (`cmsRun`)** to run the conversion
- A **Python analysis interface** (based on `uproot` + `awkward` + PyTorch) for downstream ML workflows

The goal is to bridge the gap between:

- CMSSW EDM event content (optimized for trigger and reconstruction)
- lightweight, ML-friendly representations

## Features

- Supports the following L1 Scouting objects:
  - Muons (`l1ScGmtUnpacker`)
  - Jets (`l1ScCaloUnpacker`)
  - EGammas (`l1ScCaloUnpacker`)
  - Taus (`l1ScCaloUnpacker`)
  - EtSums (`l1ScCaloUnpacker`)
  - BMTF stubs (`l1ScBMTFUnpacker`)
- Preserves **full BX structure** via explicit `bx` branches
- Stores **hardware-level quantities** (`hwPt`, `hwEta`, etc.)
- Outputs a standard ROOT `TTree` readable with `uproot`

---

## Repository structure

```
─ Ntupleizer/
  ├── plugins/
  │   ├── L1ScoutingOrbitNtupleizer.cc
  │   └── BuildFile.xml
  ├── python/
  │   └── l1scouting_ntuple_cfg.py
  ├── processl1scouting.py             # optional ML helper
  └── README.md                        # this file
```

---

## Setup

### 1. CMSSW environment

```bash
cmsrel CMSSW_16_0_0_pre2
cd CMSSW_16_0_0_pre2/src
cmsenv
```

### 2. Clone repository

```bash
mkdir L1Scouting
git clone git@github.com:uhh-pd-ml/l1scouting-ntuplizer.git L1Scouting/Ntupleizer
```

### 3. Build

```bash
scram b -j 8
```

---

## Running the ntuplizer

Example:

```bash
cmsRun L1Scouting/Ntupleizer/python/l1scouting_ntuple_cfg.py     inputFiles=file:/path/to/input.root     outputFile=l1scouting_ntuple.root     maxEvents=100
```

---

## Reading the ntuple (Python)

```python
import uproot
import awkward as ak

f = uproot.open("l1scouting_ntuple.root")
tree = f["Events"]

arrays = tree.arrays(["mu_hwPt", "jet_hwEt"], library="ak")
print(arrays[:5])
```

---

## ML-friendly interface

```bash
python processl1scouting.py l1scouting_ntuple.root
```

---

