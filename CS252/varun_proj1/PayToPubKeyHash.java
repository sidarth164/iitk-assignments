package in.ac.iitk.cse.cs252.transactions;

import org.bitcoinj.core.NetworkParameters;
import org.bitcoinj.core.Transaction;
import org.bitcoinj.crypto.DeterministicKey;
import org.bitcoinj.crypto.TransactionSignature;
import org.bitcoinj.script.Script;
import org.bitcoinj.script.ScriptBuilder;

import java.io.File;

import static org.bitcoinj.script.ScriptOpCodes.*;
import static org.bitcoinj.script.ScriptOpCodes.OP_VERIFY;

/**
 * Created by bbuenz on 24.09.15.
 */
public class PayToPubKeyHash extends ScriptTransaction {
    // TODO: Problem 1
    ECKey key = randKey();
    public PayToPubKeyHash(NetworkParameters parameters, File file, String password) {
        super(parameters, file, password);
    }

    @Override
    public Script createInputScript() {
        // TODO: Create a P2PKH script
        // TODO: be sure to test this script on the mainnet using a vanity address
            ScriptBuilder builder = new ScriptBuilder();
            builder.op(OP_DUP).op(OP_HASH160).data(key.getPubKeyHash()).op(OP_EQUALVERIFY).op(OP_CHECKSIG);
            return builder.build();
    }

    @Override
    public Script createRedemptionScript(Transaction unsignedTransaction) {
            TransactionSignature txSig = sign(unsignedTransaction, key);
            ScriptBuilder builder = new ScriptBuilder();
            builder.data(txSig.encodeToBitcoin()).data(key.getPubKey);
            return builder.build();
    }
}
