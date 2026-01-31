한글 초성 검색을 알고리즘 만으로 구현했습니다. (C++17)
```mermaid
graph TD
    A["프로그램 시작<br/>SetConsoleOutputCP/CP UTF-8"] --> B["📥 사용자 입력 받기<br/>strSearch"]
    
    B --> C["UTF-8 → wstring 변환<br/>convertUtf8ToWString"]
    C --> D["검색어 분석<br/>convertSentence"]
    
    D --> E["각 문자 판별"]
    E --> E1{"한글 음절?<br/>0xAC00~0xD7A3"}
    E1 -->|Yes| E2["한글 분해<br/>초성/중성/종성"]
    E1 -->|No| E3{"호환 자모?<br/>0x3130~0x318F"}
    E3 -->|Yes| E4["자모 변환<br/>ConvertCompatChoToJamo"]
    E3 -->|No| E5["영문 문자<br/>그대로 사용"]
    
    E2 --> E6["자음 이중화 변환<br/>convertChoToDoubleConsonant<br/>convertJongToCho"]
    E4 --> E6
    E5 --> F["vecSearch 생성<br/>variant배열"]
    E6 --> F
    
    F --> G["단어 목록 순회 시작"]
    G --> H["단어 하나 선택"]
    H --> I["단어 분석<br/>convertSentence"]
    
    I --> J["vecWord 생성<br/>variant배열"]
    J --> K{"vecWord.size ≥<br/>vecSearch.size?"}
    
    K -->|No| L["매칭 실패<br/>다음 단어"]
    K -->|Yes| M["compareSentence 실행<br/>부분 매칭 검사"]
    
    M --> N["초기화: iCorrect = 0"]
    N --> O["단어의 각 문자 순회"]
    O --> P{"vecSearch[iCorrect]<br/>타입 일치?"}
    
    P -->|No| Q["iCorrect = 0<br/>재시작"]
    P -->|Yes| R{"compare 메서드<br/>실행"}
    
    R -->|한글| R1["stHangeul::compare<br/>초/중/종성 비교"]
    R -->|영문| R2["stEnglish::compare<br/>문자 일치 비교"]
    
    R1 --> S{"일치 여부"}
    R2 --> S
    
    S -->|Match| T["iCorrect++"]
    S -->|No Match| Q
    
    T --> U{"iCorrect ≥<br/>vecSearch.size?"}
    U -->|Yes| V["매칭 성공!"]
    U -->|No| O
    
    Q --> O
    
    V --> W["단어 출력<br/>convertWStringToUtf8<br/>std::cout"]
    L --> X{"더 이상<br/>단어 있음?"}
    W --> X
    
    X -->|Yes| H
    X -->|No| Y["프로그램 종료"]
    
    style A fill:#90EE90
    style Y fill:#FFB6C6
    style V fill:#87CEEB
    style M fill:#FFD700
    style E fill:#DDA0DD
