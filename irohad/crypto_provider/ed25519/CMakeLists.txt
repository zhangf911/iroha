add_library(irohad-ed25519-signer
    ed25519signer.cpp
    )
target_link_libraries(irohad-ed25519-signer
    libs-crypto-ed25519
    )
